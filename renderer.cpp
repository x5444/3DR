#include <stdint.h>
#include <math.h>
#include "renderer.hpp"

#define PI 3.1415f

Renderer::Renderer(Vector eyePoint, Vector direction, float angle){
	this->createView(eyePoint, direction, angle);
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
    for(i = lights.begin(); i != lights.end(); i++){
        t.buildNormal(eyePoint);

        float lang = (t.middle()-(i->pos())).normalize()*t.normal(); // angle
        if(lang < 0){
            lang = 0;
        }

        Color lint = i->intensity();    // TODO: Account for light weakening
                                        // at 1/r^2
        res = res + (lang*lint);        // TODO: Overflows can happen so quickly
    }
    return res;
}
