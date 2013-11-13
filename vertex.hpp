class Vertex{

	private:
		float vx[3];

	public:
		Vertex(float x=0.0f, float y=0.0f, float z=0.0f);

		Vertex add(Vertex v);
		
        Vertex sub(Vertex v);

		Vertex scalarMult(int a);

		Vertex crossProd(Vertex v);

		float scalarProd(Vertex v);

		float *getCoordinates();
};

