#include <stdint.h>
#include <math.h>
#include <list>
#ifdef DEBUG
    #include <stdio.h>
#endif

#include "renderer.hpp"
#include "lightsource.hpp"

#define nPI 3.1415f
#define nE  2.7182f

Renderer::Renderer(Vector eyePoint, Vector direction, float angle, Scene *sc, RenderTarget *ta){
    this->s = sc;
    this->t = ta;
	this->createView(eyePoint, direction, angle);

    this->scale = fmax(ta->width(), ta->height())/2*d*tan((angle*nPI)/180);
}

void Renderer::createView(Vector eyePoint, Vector direction, float angle){
	this->eyePoint = eyePoint;
	this->direction = direction;
	this->angle = angle;

	d = direction.length();
	this->mainPoint = eyePoint + direction;

	e[0] = -direction.normalize();

	e[1].y() = 0.0f; //e1.z = 0

	if(e[0].x() == 0.0f){
        if(e[0].z() >= 0.0f){
    		e[1].x() = -1.0f;
        }else{
    		e[1].x() = 1.0f;
        }
		e[1].z() = 0.0f;
	}else{
        if(e[0].x() >= 0){
    		e[1].z() = 1.0f;
        }else{
            e[1].z() = -1.0f;
        }
		e[1].x() = -(e[1].z()*e[0].z())/e[0].x();
		e[1] = e[1].normalize();
	}

	e[2] = -(e[0]%e[1]).normalize();

    #ifdef DEBUG
        printf("e_0 = (%.2f|%.2f|%.2f)\n",e[0].x(),e[0].y(),e[0].z());
        printf("e_1 = (%.2f|%.2f|%.2f)\n",e[1].x(),e[1].y(),e[1].z());
        printf("e_2 = (%.2f|%.2f|%.2f)\n",e[2].x(),e[2].y(),e[2].z());
    #endif
}

Point Renderer::centralProject(Vector v){
    Vector vn;
    vn.z() = (v-mainPoint)*e[0];
    vn.x() = (v-mainPoint)*e[1];
    vn.y() = (v-mainPoint)*e[2];

    int sgn = 1;
    if(vn.z() > 0){ // Vector is behind the projection area
        sgn = -1;
    }

    float px, py;
    px = vn.x()/(1-(vn.z()/d));
    py = vn.y()/(1-(vn.z()/d));

    return Point(px, py, sgn*(v-eyePoint).length()); 
}

Color Renderer::getBrightness(Triangle t){
    Color res = Color();
    std::list<LightSource>::iterator i;
    for(i = s->lights.begin(); i != s->lights.end(); i++){
        t.buildNormal(eyePoint);

        float lang = (t.middle()-(i->pos)).normalize()*t.normal(); // angle
        if(lang < 0){
            lang = 0;
        }

        Color lint = i->intensity;  // TODO: Account for light weakening
                                    // at 1/r^2
        res = res + (lang*lint);
    }

    res = res + s->globalBr.intensity;

    // This function is horrible, but it converges to 1, reaches 0.9 at x=1 and
    // has a slope of 8 at x=0
    res.r() = (nE - exp(1/(5*res.r()+1)))/(nE-1);
    res.g() = (nE - exp(1/(5*res.g()+1)))/(nE-1);
    res.b() = (nE - exp(1/(5*res.b()+1)))/(nE-1);
    
    return res;
}

void Renderer::drawLowerTriangle(Point p1, Point p2, Point p3, Color c){
    #ifdef DEBUG
        printf("drawUpperTriangle(T1,T2,T3)\n");
        printf("T1: (%.2f|%.2f|%.2f)\n",p1.x(),p1.y(),p1.dist());
        printf("T2: (%.2f|%.2f|%.2f)\n",p2.x(),p2.y(),p2.dist());
        printf("T3: (%.2f|%.2f|%.2f)\n",p3.x(),p3.y(),p3.dist());
    #endif

    const int yStart = p1.yi();
    const int yEnd = p3.yi(); // Equal to p3.yi in this case

    const int x_l = p1.xi() - p2.xi();
    const int x_r = p3.xi() - p1.xi();
    const int h = p2.yi() - p1.yi()+1;

    int xStart = p1.xi();   // These will vary during runtime
    int xEnd = p1.xi();

    // f(x,y) = mx + ny + t
    //      m = (p3.dist() - p2.dist()) / (p3.x() - p2.x())
    float m = (p3.dist() - p2.dist()) / (p3.x() - p2.x());

    //      n = (ph.dist() - p1.dist()) / (ph.y() - p1.y())
    //          ph is between p1 and p2 with ph.x() = p3.x()
    //              and ph.y is p2.y and ph.dist() is
    //              m*(ph.x()-p2.x()) + p2.dist()
    Point ph(p1.x(), p2.y(), 0);
    ph.dist() = m*(ph.x()-p2.x()) + p2.dist();
    float n = (ph.dist() - p1.dist()) / (ph.y() - p1.y());

    // t = p1.dist() - n*p1.y() - m*p1.x()     -- That's what maxima said
    float st = p1.dist() - n*p1.y() - m*p1.x();
    #ifdef DEBUG
        printf("d = %.2f*x + %.2f*y + %2.f\n", m,n,st);
    #endif

    for(int y=yStart; y<=yEnd; y++){
        xStart = p1.xi()-(((float)(y-yStart+1)/(float)h)*x_l);
        xEnd = p1.xi()+(((float)(y-yStart+1)/(float)h)*x_r);

        for(int x=xStart; x<=xEnd; x++){
            float depth = m*x + n*y + st;

            if(depth > 0 and depth < t->zb(x,y)){
                t->fb(x,y) = c.toInt();
            }
        }
    }
}

void Renderer::drawUpperTriangle(Point p1, Point p2, Point p3, Color c){
    #ifdef DEBUG
        printf("drawUpperTriangle(T1,T2,T3)\n");
        printf("T1: (%.2f|%.2f|%.2f)\n",p1.x(),p1.y(),p1.dist());
        printf("T2: (%.2f|%.2f|%.2f)\n",p2.x(),p2.y(),p2.dist());
        printf("T3: (%.2f|%.2f|%.2f)\n",p3.x(),p3.y(),p3.dist());
    #endif

    const int yStart = p1.yi(); // Equal to p2.yi in this case
    const int yEnd = p3.yi();

    const int x_l = p3.xi() - p1.xi();
    const int x_r = p2.xi() - p3.xi();
    const int h = p3.yi() - p1.yi()+1;

    int xStart = p1.xi();   // These will vary during runtime
    int xEnd = p2.xi();

    // f(x,y) = mx + ny + t
    //      m = (p3.dist() - p2.dist()) / (p3.x() - p2.x())
    float m = (p2.dist() - p1.dist()) / (p2.x() - p1.x());

    //      n = (ph.dist() - p1.dist()) / (ph.y() - p1.y())
    //          ph is between p1 and p2 with ph.x() = p3.x()
    //              and ph.y is p2.y and ph.dist() is
    //              m*(ph.x()-p2.x()) + p2.dist()
    Point ph(p3.x(), p2.y(), 0);
    ph.dist() = m*(ph.x()-p2.x()) + p2.dist();
    float n = (ph.dist() - p3.dist()) / (ph.y() - p3.y());

    // t = p1.dist() - n*p1.y() - m*p1.x()     -- That's what maxima said
    float st = p1.dist() - n*p1.y() - m*p1.x();
    #ifdef DEBUG
        printf("d = %.2f*x + %.2f*y + %2.f\n", m,n,st);
    #endif

    for(int y=yStart; y<=yEnd; y++){
        xStart = p3.xi()-(((float)(yEnd-y+1)/(float)h)*x_l);
        xEnd = p3.xi()+(((float)(yEnd-y+1)/(float)h)*x_r);

        for(int x=xStart; x<=xEnd; x++){
            float depth = m*x + n*y + st;

            if(depth > 0 and depth < t->zb(x,y)){
                t->fb(x,y) = c.toInt();
            }
        }
    }

}

void Renderer::renderTriangle(Triangle tr){
    tr.buildNormal(this->eyePoint);

    #ifdef DEBUG
        printf("\nStarting a new Triangle:\n");
    #endif

    Point p[3];
    int sgn = 0;
    for(int i=0; i<3; i++){
        p[i] = ((fmax(t->height(), t->width())/2)*Point(1,1,0))+(this->centralProject(tr.v[i])*this->scale);

        if(t->height() < t->width()){
            p[i].y() -= (t->width()-t->height())/2;
        }
        if(t->height() > t->width()){
            p[i].x() -= (t->height()-t->width())/2;
        }
        
        if(p[i].dist() > 0){
            sgn = 1;
        }
    }

    Color br = this->getBrightness(tr);
    //printf("%.2f,%.2f,%.2f\n",br.r(), br.g(), br.b());
    if(sgn==0){
        #ifdef DEBUG
            printf("Triangle behind projection area\n");
        #endif
        return;
    }
    //TODO: return if triangle is fully out of screen

    // Sort Points by y coordinate, then by x coordinate
    // TODO: Use std::sort for this?!
    Point pb;
    if(p[1].y() < p[0].y()){
        pb = p[0];
        p[0] = p[1];
        p[1] = pb;
    }
    if(p[2].y() < p[1].y()){
        pb = p[1];
        p[1] = p[2];
        p[2] = pb;
    }
    if(p[1].y() < p[0].y()){
        pb = p[0];
        p[0] = p[1];
        p[1] = pb;
    }
    if(p[0].y()==p[1].y() && p[1].x() < p[0].x()){
        pb = p[0];
        p[0] = p[1];
        p[1] = pb;
    }
    if(p[1].y()==p[2].y() && p[2].x() < p[1].x()){
        pb = p[1];
        p[1] = p[2];
        p[2] = pb;
    }

    #ifdef DEBUG
        for(int i=0;i<3;i++){
            printf("T%i: (%.2f|%.2f|%.2f)\n",i,p[i].x(),p[i].y(),p[i].dist());
        }
    #endif
        

    // Actually draw our trianlge
    if(p[0].y() == p[1].y()){
        drawUpperTriangle(p[0], p[1], p[2], tr.c[0]*br);
    }else if(p[1].y() == p[2].y()){
        drawLowerTriangle(p[0], p[1], p[2], tr.c[0]*br);
    }else{
        // Generate helper point ph
        float yh = p[1].y();
        float xh = p[2].x() - (p[2].x()-p[0].x()) * (p[2].y()-p[1].y())/(p[2].y()-p[0].y()); // Awful code is awful.
        Point ph(xh, yh, 0);
        if(p[2].x() != p[0].x()){
            ph.dist() = p[1].dist() + (ph.x()-p[0].x())*((p[2].dist()-p[0].dist())/(p[2].x()-p[0].x()));
        }else{
            ph.dist() = p[1].dist() + (ph.x()-p[1].x())*((p[2].dist()-p[1].dist())/(p[2].x()-p[1].x()));
        }

        // TODO: Fill ph.depth
        if(ph.x() < p[1].x()){
            drawLowerTriangle(p[0], ph, p[1], tr.c[0]*br);
            drawUpperTriangle(ph, p[1], p[2], tr.c[0]*br);
        }else{
            drawLowerTriangle(p[0], p[1], ph, tr.c[0]*br);
            drawUpperTriangle(p[1], ph, p[2], tr.c[0]*br);
        }
    }
}

void Renderer::renderScene(){
    std::list<Triangle>::iterator i;
    for(i=s->triags.begin(); i!=s->triags.end(); i++){
        this->renderTriangle(*i);
    }
}

