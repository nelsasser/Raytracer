#pragma once
#include "Primitives/Primitive.h"

class Light {
public:
	Vec3 position;
	Color color;
	Light(Vec3, Color);
	~Light();
};

