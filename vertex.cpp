#include <stdint.h>
#include <stdio.h>
#include "Vertex.hpp"

Vertex::Vertex(float x, float y, float z){
	vx[0] = x;
	vx[1] = y;
	vx[2] = z;
	return;
}		

Vertex Vertex::scalarMult(int a, Vertex v){
	return Vertex(v.getCoordinates()[0]*a, v.getCoordinates()[1]*a, v.getCoordinates()[2]*a);
}

Vertex Vertex::operator+(Vertex& right){
	return Vertex(this->vx[0]+right.vx[0], this->vx[1]+right.vx[1], this->vx[2]+right.vx[2]);
}

Vertex Vertex::operator-(Vertex& right){
	return Vertex(this->vx[0]-right.vx[0], this->vx[1]-right.vx[1], this->vx[2]-right.vx[2]);
}

float Vertex::operator*(Vertex& right){
	float res=0;
	for(int i=0; i<3; i++){
		res += this->vx[i]*right.getCoordinates()[i];
	}
	return res;
}

float *Vertex::getCoordinates(){
	return vx;
}

Vertex operator*(int left, Vertex& right){
	return scalarMult(left, right);
}

Vertex operator*(Vertex& right, int left){
	return scalarMult(left, right);
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
