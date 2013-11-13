class Vector{

	private:
		float vx[3];

	public:
		Vector(float x=0.0f, float y=0.0f, float z=0.0f);

		Vector add(Vector v);
		
        Vector sub(Vector v);

		Vector scalarMult(int a);

		Vector crossProd(Vector v);

        float& operator[](int i);

		float scalarProd(Vector v);

        float length();

		float *getCoordinates();
};

