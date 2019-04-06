#pragma once
#include "Shape.h"
#include <tuple>

class Sphere : public Shape {
private:
	float radius;
	Vec3 position;
public:
	Color color;
	std::tuple<Vec3 *, Vec3 *> intersectsRay(Ray) override;
	Sphere(Vec3, float, Color);
	~Sphere();
};

