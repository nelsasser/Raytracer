#pragma once
#include <ostream>

struct Color {
	int r, g, b, a;

	Color() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0;
	}

	Color(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}

	Color(int r, int g, int b, int a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color operator * (float f) {
		return Color(r * f, g * f, b * f, a * f);
	}

	Color operator * (Color c) {
		return Color(r * c.r, g * c.g, b * c.b, a * c.a);
	}

	Color operator - (Color c) {
		return Color(r - c.r, g - c.g, b - c.b, a - c.a);
	}

	Color operator + (Color c) {
		return Color(r + c.r, g + c.g, b + c.b, a + c.a);
	}

	void clamp() {
		this->r = (r > 255) ? 255 : (r < 0) ? 0: r;
		this->g = (g > 255) ? 255 : (g < 0) ? 0: g;
		this->b = (b > 255) ? 255 : (b < 0) ? 0: b;
		this->a = (a > 255) ? 255 : (a < 0) ? 0: a;
	}

	std::ostream& operator<< (std::ostream& os) const {
		os << r << ", " << g << ", " << b << ", " << a;
		return os;
	}

};

struct Vec3
{
	float x, y, z;

	Vec3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3 operator * (float c) {
		return Vec3(this->x * c, this->y * c, this->z * c);
	}

	Vec3 operator + (Vec3 v) {
		return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
	}
};

struct Mat3x3
{
	float *mat;

	Mat3x3()
	{
		mat = new float[9];
		for(int i = 0; i < 9; i++) {
			mat[i] = 0;
		}
	}

	Mat3x3(float m[9]) {
		mat = m;
	}

	Mat3x3 operator + (Mat3x3 m) const {
		float newMat[9];
		for(int i = 0; i < 9; i++) {
			newMat[i] = mat[i] + m.mat[i];
		}
		return { newMat };
	}

	Mat3x3 operator * (Mat3x3 m) const {
		float newMat[9];
		for(int row = 0; row < 3; row++) {
			for(int col = 0; col < 3; col++) {
				float sum = 0;
				for(int i = 0; i < 3; i++) {
					sum += mat[row * 3 + i] * m.mat[col + i * 3];
				}
				newMat[row * 3 + col] = sum;
			}
		}
		return { newMat };
	}

	Mat3x3 operator * (float f) const {
		float newMat[9];
		for(int i = 0; i < 9; i++) {
			newMat[i] = mat[i] * f;
		}
		return { newMat };
	}

	Vec3 operator * (Vec3 v) const {
		float c[3];
		for(int i = 0; i < 3; i++) {
			float sum = 0;
			for(int j = 0; j < 3; j++) {
				sum += mat[i * 3 + j] * (j==0)?v.x:(j==1)?v.y:(j==2)?v.z:0;
			}
			c[i] = sum;
		}
		return { c[0], c[1], c[2] };
	}
};

class Primitive
{
public:
	Primitive();

	static Vec3 UP;
	static Vec3 LEFT;
	static Vec3 RIGHT;
	static Vec3 DOWN;
	static Vec3 FORWARD;
	static Vec3 BACK;

	static Mat3x3 I;

	static Vec3 Vec3Norm(Vec3);
	static float Vec3Dot(Vec3, Vec3);
	static Vec3 Vec3Cross(Vec3, Vec3);
	static float Vec3Length(Vec3);
};