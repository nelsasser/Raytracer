#pragma once
#include "Primitive.h"

class Ray {
public:
	Vec3 start;
	Vec3 direction;
	Vec3 unitDirection;

	Ray(Vec3, Vec3);
	~Ray();
};

