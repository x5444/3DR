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

		Vector add(Vector v);
		
        Vector sub(Vector v);

		Vector scalarMult(int a);

		Vector crossProd(Vector v);

        Vector normalize();

        float& operator[](int i);

		float scalarProd(Vector v);

        float length();

        float invSqrt(float x);
};

