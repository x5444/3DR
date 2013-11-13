#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "vertex.hpp"

Vector::Vector(float x, float y, float z){
	vx[0] = x;
	vx[1] = y;
	vx[2] = z;
	return;
}

Vector Vector::add(Vector v){
    Vector res;
    res.vx[0] = this->vx[0]+v.getCoordinates()[0];
    res.vx[1] = this->vx[1]+v.getCoordinates()[1];
    res.vx[2] = this->vx[2]+v.getCoordinates()[2];
    return res;
}

Vector Vector::sub(Vector v){
    Vector res;
    res.vx[0] = this->vx[0]-v.getCoordinates()[0];
    res.vx[1] = this->vx[1]-v.getCoordinates()[1];
    res.vx[2] = this->vx[2]-v.getCoordinates()[2];
    return res;
}

Vector Vector::scalarMult(int a){
	return Vector(this->vx[0]*a, this->vx[1]*a, this->vx[2]*a);
}

Vector Vector::crossProd(Vector v){
    Vector res;
    res.vx[0] = this->vx[1]*v.getCoordinates()[2] - this->vx[2]*v.getCoordinates()[1];
    res.vx[1] = this->vx[2]*v.getCoordinates()[0] - this->vx[0]*v.getCoordinates()[2];
    res.vx[2] = this->vx[0]*v.getCoordinates()[1] - this->vx[1]*v.getCoordinates()[0];
    return res;
}

float Vector::scalarProd(Vector v){
	float res=0;
	for(int i=0; i<3; i++){
		res += this->vx[i]*v.getCoordinates()[i];
	}
	return res;
}

float Vector::length(){
    return sqrt(this->vx[0]*this->vx[0] + this->vx[1]*this->vx[1] + this->vx[2]*this->vx[2]);
}

float& Vector::operator[](int i){
    return this->vx[i];
}

Vector operator+(Vector& v1, Vector& v2){
    return v1.add(v2);
}

Vector operator-(Vector& v1, Vector& v2){
    return v1.sub(v2);
}
    
float *Vector::getCoordinates(){
	return vx;
}

Vector operator*(int a, Vector& v){
	return v.scalarMult(a);
}

Vector operator*(Vector& v, int a){
	return v.scalarMult(a);
}

Vector operator%(Vector& v1, Vector& v2){
    return v1.crossProd(v2);
}

float operator*(Vector& v1, Vector& v2){
    return v1.scalarProd(v2);
}

float operator~(Vector& v){
    return v.length();
}


int main(){
	printf("\n\n\n");

	Vector a(1,2,3), b(3,2,2);
	printf("%.2f, %.2f, %.2f\n", (a-b)[0], (a-b)[1], (a+b)[2]);
	printf("%.2f, %.2f, %.2f\n", (3*a)[0], (3*a)[1], (3*a)[2]);
	printf("%.2f, %.2f, %.2f\n", (a*3)[0], (a*3)[1], (a*3)[2]);
	printf("%.2f\n", (a*b));
    printf("%.2f\n", ~a);

	printf("\n\n\n");
}
