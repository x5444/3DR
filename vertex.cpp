#include <stdint.h>
#include <stdio.h>
#include "vertex.hpp"

Vertex::Vertex(float x, float y, float z){
	vx[0] = x;
	vx[1] = y;
	vx[2] = z;
	return;
}

Vertex Vertex::add(Vertex v){
    Vertex res;
    res.vx[0] = this->vx[0]+v.getCoordinates()[0];
    res.vx[1] = this->vx[1]+v.getCoordinates()[1];
    res.vx[2] = this->vx[2]+v.getCoordinates()[2];
    return res;
}

Vertex Vertex::sub(Vertex v){
    Vertex res;
    res.vx[0] = this->vx[0]-v.getCoordinates()[0];
    res.vx[1] = this->vx[1]-v.getCoordinates()[1];
    res.vx[2] = this->vx[2]-v.getCoordinates()[2];
    return res;
}

Vertex Vertex::scalarMult(int a){
	return Vertex(this->vx[0]*a, this->vx[1]*a, this->vx[2]*a);
}

Vertex Vertex::crossProd(Vertex v){
    Vertex res;
    res.vx[0] = this->vx[1]*v.getCoordinates()[2] - this->vx[2]*v.getCoordinates()[1];
    res.vx[1] = this->vx[2]*v.getCoordinates()[0] - this->vx[0]*v.getCoordinates()[2];
    res.vx[2] = this->vx[0]*v.getCoordinates()[1] - this->vx[1]*v.getCoordinates()[0];
    return res;
}

float Vertex::scalarProd(Vertex v){
	float res=0;
	for(int i=0; i<3; i++){
		res += this->vx[i]*v.getCoordinates()[i];
	}
	return res;
}

Vertex operator+(Vertex& v1, Vertex& v2){
    return v1.add(v2);
}

Vertex operator-(Vertex& v1, Vertex& v2){
    return v1.sub(v2);
}
    
float *Vertex::getCoordinates(){
	return vx;
}

Vertex operator*(int a, Vertex& v){
	return v.scalarMult(a);
}

Vertex operator*(Vertex& v, int a){
	return v.scalarMult(a);
}

Vertex operator%(Vertex& v1, Vertex& v2){
    return v1.crossProd(v2);
}

float operator*(Vertex& v1, Vertex& v2){
    return v1.scalarProd(v2);
}


int main(){
	printf("\n\n\n");

	Vertex a(1,2,3), b(3,2,2);
	printf("%.2f, %.2f, %.2f\n", (a-b).getCoordinates()[0], (a-b).getCoordinates()[1], (a+b).getCoordinates()[2]);
	printf("%.2f, %.2f, %.2f\n", (3*a).getCoordinates()[0], (3*a).getCoordinates()[1], (3*a).getCoordinates()[2]);
	printf("%.2f, %.2f, %.2f\n", (a*3).getCoordinates()[0], (a*3).getCoordinates()[1], (a*3).getCoordinates()[2]);
	printf("%.2f\n", (a*b));

	printf("\n\n\n");
}
