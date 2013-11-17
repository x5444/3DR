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

    float px, py;
    px = vn.x()/(1-(vn.z()/d));
    py = vn.y()/(1-(vn.z()/d));

    return Point(px, py, vn.length()); 
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

void Renderer::renderTriangle(Triangle tr){
    tr.buildNormal(this->eyePoint);

    printf("\nStarting a new Triangle:\n");

    Point p[3];
    for(int i=0; i<3; i++){
        p[i] = ((fmax(t->height(), t->width())/2)*Point(1,1,0))+(this->centralProject(tr.v[i])*this->scale);
        printf("%i,%i|%.2f\n",p[i].xi(),p[i].yi(),p[i].dist());
    }

    Color br = this->getBrightness(tr);
    //printf("%.2f,%.2f,%.2f\n",br.r(), br.g(), br.b());
}
