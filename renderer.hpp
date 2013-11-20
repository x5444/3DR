#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "vector.hpp"
#include "triangle.hpp"
#include "point.hpp"
#include "scene.hpp"
#include "rendertarget.hpp"

class Renderer{
	private:
		Vector 	e[3];
		Vector 	eyePoint;
		Vector 	mainPoint;
		Vector 	direction;
		float	d;
		float	angle;
        float   scale;

        Scene   *s;
        RenderTarget *t;

        void drawUpperTriangle(Point p1, Point p2, Point p3, Color c);
        void drawLowerTriangle(Point p1, Point p2, Point p3, Color c);

	public:
		Renderer(Vector eyePoint, Vector direction, float angle, Scene *sc, RenderTarget *ta);

		Point centralProject(Vector v);

		void createView(Vector eyePoint, Vector direction, float angle);

        Color getBrightness(Triangle t);

        void renderTriangle(Triangle t);

        void renderScene();
};

#endif // __RENDERER_HPP__
