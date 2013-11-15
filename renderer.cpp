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

	e[1][2] = 0.0f; //e1.z = 0
	if(e[0][0] == 0.0f){
		e[1][0] = 1.0f;
		e[1][1] = 0.0f;
	}else{
		e[1][1] = 1.0f;
		e[1][0] = -(e[1][1]*e[0][1])/e[0][0];
		e[1] = e[1].normalize();
	}

	e[2] = (e[0]%e[1]).normalize();
}
