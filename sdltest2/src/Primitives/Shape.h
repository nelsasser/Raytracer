#pragma once
#include "Ray.h"
#include <tuple>

class Shape {
public:
	virtual std::tuple<Vec3 *, Vec3 *> intersectsRay(Ray) = 0;
	Shape();
	~Shape();
};

