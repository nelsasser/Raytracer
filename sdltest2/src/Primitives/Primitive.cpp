#include "Primitive.h"
#include <complex>

Vec3 Primitive::UP = Vec3(0, 0, 1);
Vec3 Primitive::DOWN = Vec3(0, 0, -1);
Vec3 Primitive::FORWARD = Vec3(1, 0, 0);
Vec3 Primitive::BACK = Vec3(-1, 0, 0);
Vec3 Primitive::LEFT = Vec3(0, -1, 0);
Vec3 Primitive::RIGHT = Vec3(0, 1, 0);

float identityMatrixArray[9] = {1, 0, 0,
								0, 1, 0,
								0, 0, 1};

Mat3x3 Primitive::I = Mat3x3(identityMatrixArray);

float Primitive::Vec3Length(Vec3 v) {
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}


Vec3 Primitive::Vec3Norm(Vec3 v) {
	float L = 1 / Vec3Length(v);
	return v * L;
}

float Primitive::Vec3Dot(Vec3 v1, Vec3 v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vec3 Primitive::Vec3Cross(Vec3 v1, Vec3 v2) {
	float nx = v1.y * v2.z - v1.z * v2.y;
	float ny = v1.z * v2.x - v1.x * v2.z;
	float nz = v1.x * v2.y - v1.y * v2.x;
	
	return Vec3(nx, ny, nz);
}


