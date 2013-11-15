#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <list>
#include "vector.hpp"
#include "triangle.hpp"
#include "point.hpp"
#include "lightsource.hpp"

class Renderer{
	private:
		Vector 	e[3];
		Vector 	eyePoint;
		Vector 	mainPoint;
		Vector 	direction;
		float	d;
		float	angle;

        std::list<LightSource> lights;

	public:
		Renderer(Vector eyePoint, Vector direction, float angle);

		Point centralProject(Vector v);

		void createView(Vector eyePoint, Vector direction, float angle);

        Color getBrightness(Triangle t);
};

#endif // __RENDERER_HPP__
