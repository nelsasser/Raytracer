#include "Sphere.h"
#include <cmath>

Sphere::Sphere(Vec3 position, float radius, Color color) {
	this->position = position;
	this->radius = radius;
	this->color = color;
}

std::tuple<Vec3 *, Vec3 *> Sphere::intersectsRay(Ray ray) {
	//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
	//solve a^2x + bx + c = 0

	float a = 1.0;
	float b = 2 * Primitive::Vec3Dot(ray.unitDirection, ray.start + (this->position * -1));
	float ocMag = Primitive::Vec3Length(ray.start + (this->position * -1));
	float c = ocMag * ocMag - this->radius * this->radius;

	float x0, x1;

	float discr = b * b - 4 * a * c;

	if (discr < 0) {
		return std::make_tuple(nullptr, nullptr);
	}

	
	if (discr == 0) {
		x0 = x1 = -0.5 * b / a;
	} else { 
		float q = (b > 0) ? 
			-0.5 * (b + sqrt(discr)) : 
			-0.5 * (b - sqrt(discr)); 
		x0 = q / a; 
		x1 = c / q; 
	}
	
	if (x0 > x1) {
		float temp = x0;
		x0 = x1;
		x1 = temp;
	}

	Vec3 normal = Primitive::Vec3Norm((ray.start + ray.unitDirection * ((x0<x1)?x0:x1)) + (this->position * -1));

	return std::make_tuple(&normal, &(ray.start + ray.unitDirection * ((x0<x1)?x0:x1)));
}


Sphere::~Sphere() {}
