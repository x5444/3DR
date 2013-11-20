#include <stdint.h>
#include <math.h>
#include <list>

#include <stdio.h>

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
		e[1].x() = 1.0f;
		e[1].z() = 0.0f;
	}else{
		e[1].z() = 1.0f;
		e[1].x() = -(e[1].z()*e[0].z())/e[0].x();
		e[1] = -e[1].normalize();
	}

	e[2] = (e[0]%e[1]).normalize();
}

Point Renderer::centralProject(Vector v){
    Vector vn;
    vn.z() = (v-mainPoint)*e[0];
    vn.x() = (v-mainPoint)*e[1];
    vn.y() = (v-mainPoint)*e[2];

    int sgn = 1;
    if(vn.z() > 0){ // Vector is behind 
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
    //printf("drawUpperTriag\n");
    const int yStart = p1.yi();
    const int yEnd = p3.yi(); // Equal to p3.yi in this case

    const int x_l = p1.xi() - p2.xi();
    const int x_r = p3.xi() - p1.xi();
    const int h = p2.yi() - p1.yi()+1;
    //printf("%i\n", h);

    int xStart = p1.xi();   // These will vary during runtime
    int xEnd = p1.xi();

    for(int y=yStart; y<=yEnd; y++){
        xStart = p1.xi()-(((float)(y-yStart)/(float)h)*x_l);
        xEnd = p1.xi()+(((float)(y-yStart+1)/(float)h)*x_r);
        //printf("%i,%i|%i\n", xStart, xEnd,y);

        for(int x=xStart; x<=xEnd; x++){
            t->fb(x,y) = c.toInt();
            //printf("%x|", c.toInt());
        }
    }

    //printf("%i,%i\n", yStart, yEnd);
}

void Renderer::drawUpperTriangle(Point p1, Point p2, Point p3, Color c){
    //printf("drawLowerTriag\n");
    const int yStart = p1.yi(); // Equal to p2.yi in this case
    const int yEnd = p3.yi();

    const int x_l = p3.xi() - p1.xi();
    const int x_r = p2.xi() - p3.xi();
    const int h = p3.yi() - p1.yi()+1;
    //printf("%i\n", h);

    int xStart = p1.xi();   // These will vary during runtime
    int xEnd = p2.xi();

    for(int y=yStart; y<=yEnd; y++){
        xStart = p3.xi()-(((float)(yEnd-y)/(float)h)*x_l);
        xEnd = p3.xi()+(((float)(yEnd-y+1)/(float)h)*x_r);
        //printf("%i,%i\n", xStart, xEnd);

        for(int x=xStart; x<=xEnd; x++){
            t->fb(x,y) = c.toInt();
        }
    }

    //printf("%i,%i\n", yStart, yEnd);
}

void Renderer::renderTriangle(Triangle tr){
    tr.buildNormal(this->eyePoint);

    //printf("\nStarting a new Triangle:\n");

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
        
        //printf("%i,%i|%.2f\n",p[i].xi(),p[i].yi(),p[i].dist());
        if(p[i].dist() > 0){
            sgn = 1;
        }
    }

    Color br = this->getBrightness(tr);
    //printf("%.2f,%.2f,%.2f\n",br.r(), br.g(), br.b());
    if(sgn==0){
        //printf("Triangle behind projection area\n");
        return;
    }

    // for(int i=0; i<3; i++){
    //     p[i].y() = t->height() - p[i].y();
    // }

    // Sort Points by y coordinate, then by x coordinate
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
    for(int i=0; i<3; i++){
        //printf("%i,%i|%.2f\n",p[i].xi(),p[i].yi(),p[i].dist());
    }
        

    // Actually draw our trianlge
    if(p[0].y() == p[1].y()){
        drawUpperTriangle(p[0], p[1], p[2], tr.c[0]*br);
    }else if(p[1].y() == p[2].y()){
        drawLowerTriangle(p[0], p[1], p[2], tr.c[0]*br);
    }else{
        // Generate helper point ph
        int yh = p[1].y();
        int xh = p[2].x() - (p[2].x()-p[0].x()) * (p[2].y()-p[1].y())/(p[2].y()-p[0].y());
        //float dh = (p[0]-p[2]).length();
        Point ph(xh, yh, 0);
        printf("(%i|%i)(%i|%i)(%i|%i)(%i|%i)\n",p[0].xi(),p[0].yi(),p[1].xi(),p[1].yi(),p[2].xi(),p[2].yi(),ph.xi(),ph.yi());
        drawLowerTriangle(p[0], ph, p[1], tr.c[0]*br);
        drawUpperTriangle(ph, p[1], p[2], tr.c[0]*br);
        //printf("NIY\n");
    }
}

void Renderer::renderScene(){
    std::list<Triangle>::iterator i;
    for(i=s->triags.begin(); i!=s->triags.end(); i++){
        this->renderTriangle(*i);
    }
}

