#include <stdint.h>
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

float& Vector::x(){
    return this->vx[0];
}

float& Vector::y(){
    return this->vx[1];
}

float& Vector::z(){
    return this->vx[2];
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

Vector operator+(Vector v1, Vector v2){
    return v1.add(v2);
}

Vector operator-(Vector v1, Vector v2){
    return v1.sub(v2);
}
    
Vector operator*(int a, Vector v){
	return v.scalarMult(a);
}

Vector operator*(Vector v, int a){
	return v.scalarMult(a);
}

Vector operator%(Vector v1, Vector v2){
    return v1.crossProd(v2);
}

Vector operator!(Vector v){
    return v.normalize();
}

Vector operator-(Vector v){
    return (-1)*v;
}

float operator*(Vector v1, Vector v2){
    return v1.scalarProd(v2);
}

float operator~(Vector v){
    return v.length();
}

