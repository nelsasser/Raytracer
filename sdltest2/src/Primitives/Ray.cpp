#include "Ray.h"



Ray::Ray(Vec3 start, Vec3 direction) {
	this->start = start;
	this->direction = direction;
	this->unitDirection = Primitive::Vec3Norm(this->direction + (this->start * -1));
}


Ray::~Ray() {}
