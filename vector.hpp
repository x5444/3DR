#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

/*
    Vector Lib

    Just does the very basics:
        ~   Is length of a vector
        !   Is the normalized Vector
        +   Is the sum
        -   Is the subtraction
        *   Is scalar product or scalar multiplication
        %   Is cross product
        []  Gets you the individual elements
*/

class Vector{

	private:
		float vx[3];

	public:
		Vector(float x=0.0f, float y=0.0f, float z=0.0f);

        float& x();

        float& y();

        float& z();

		Vector add(Vector v);
		
        Vector sub(Vector v);

		Vector scalarMult(float a);

		Vector crossProd(Vector v);

        Vector normalize();

        float& operator[](int i);

		float scalarProd(Vector v);

        float length();

        float invSqrt(float x);
};

Vector operator+(Vector v1, Vector v2);

Vector operator-(Vector v1, Vector v2);
    
Vector operator*(float a, Vector v);

Vector operator*(Vector v, float a);

Vector operator%(Vector v1, Vector v2);

Vector operator!(Vector v);

Vector operator-(Vector v);

float operator*(Vector v1, Vector v2);

float operator~(Vector v);

#endif // __VECTOR_HPP__
