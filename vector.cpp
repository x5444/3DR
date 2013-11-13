#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "vector.hpp"

//yeeeeeah
float Vector::invSqrt(float x)
{
    float xhalf = 0.5f*x;
    int32_t i = *(int32_t*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
}

Vector::Vector(float x, float y, float z){
	vx[0] = x;
	vx[1] = y;
	vx[2] = z;
	return;
}

Vector Vector::add(Vector v){
    Vector res;
    res.vx[0] = this->vx[0]+v[0];
    res.vx[1] = this->vx[1]+v[1];
    res.vx[2] = this->vx[2]+v[2];
    return res;
}

Vector Vector::sub(Vector v){
    Vector res;
    res.vx[0] = this->vx[0]-v[0];
    res.vx[1] = this->vx[1]-v[1];
    res.vx[2] = this->vx[2]-v[2];
    return res;
}

Vector Vector::scalarMult(int a){
	return Vector(this->vx[0]*a, this->vx[1]*a, this->vx[2]*a);
}

Vector Vector::crossProd(Vector v){
    Vector res;
    res.vx[0] = this->vx[1]*v[2] - this->vx[2]*v[1];
    res.vx[1] = this->vx[2]*v[0] - this->vx[0]*v[2];
    res.vx[2] = this->vx[0]*v[1] - this->vx[1]*v[0];
    return res;
}

Vector Vector::normalize(){
    float fact = this->invSqrt(this->vx[0]*this->vx[0] + this->vx[1]*this->vx[1] + this->vx[2]*this->vx[2]);
    Vector res;
    res[0] = this->vx[0]*fact;
    res[1] = this->vx[1]*fact;
    res[2] = this->vx[2]*fact;
    return res;
}

float Vector::scalarProd(Vector v){
	float res=0;
	for(int i=0; i<3; i++){
		res += this->vx[i]*v[i];
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
    
Vector operator*(int a, Vector& v){
	return v.scalarMult(a);
}

Vector operator*(Vector& v, int a){
	return v.scalarMult(a);
}

Vector operator%(Vector& v1, Vector& v2){
    return v1.crossProd(v2);
}

Vector operator!(Vector& v){
    return v.normalize();
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
