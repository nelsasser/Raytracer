#pragma once
#include "Primitives/Primitive.h"
#include "Primitives/Ray.h"

class Camera {
public:
	Vec3 localUp;
	Vec3 localRight;
	Vec3 localForward;
	Vec3 position;
	Vec3 direction;
	float renderPlaneDistance;
	int windowWidth;
	int windowHeight;
	Camera(Vec3, Vec3, float, int, int);
	~Camera();

	Ray castRay(float, float);
};

