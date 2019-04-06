#include "Camera.h"
#include <iostream>

Camera::Camera(Vec3 position, Vec3 direction, float renderPlaneDistance, int windowWidth, int windowHeight) {
	this->position = position;
	this->direction = direction;
	this->renderPlaneDistance = renderPlaneDistance;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}


Camera::~Camera() {}

Ray Camera::castRay(float x, float y) {

	//get unit vector for the direction the camera is facing
	Vec3 unitDirection = Primitive::Vec3Norm(this->direction);
	
	//gets the position of the center of the rendering plane
	Vec3 renderPlaneCenter = unitDirection * renderPlaneDistance + this->position;

	//normalize x and y coordinates to fit into the render plane
	//(0, 0) [x, y] becomes (-0.5, -0.5) [x-norm, y-norm] as that is location of x and y on screen relative to center of render plane
	float xNorm = (float)(x - (windowWidth / 2)) / windowWidth;
	float yNorm = (float)(y - (windowHeight / 2)) / windowHeight;

	//y becomes z and x becomes y in 3d, (right handed coordinate system)
	Vec3 pixelCoords(0, xNorm, yNorm);

	//TODO: Modify this stuff below so that we can render from camera at any point in space, at any angle. Currently only works when facing FORWARD at origin
	/*

	//In this 3d coordinate system: 
	//	x => in and out of screen
	//	y => left and right on screen
	//	z => up and down on screen
	//
	//in this case y is up on our screens, but z is up in 3D, so switch y and z (b/c i'm a hack)
	//and y is left right in our 3d space, so switch x and y 
	//get normal and magnitude of pixelCoords
	Vec3 pixelCoordsNormal = Primitive::Vec3Norm(pixelCoords);
	float pixelCoordsMagnitude = Primitive::Vec3Length(pixelCoords);

	//need to rotate pixel coords so render plane is perpendicular to the direction the camera is facing

	//steps:
	//	1) rotate camera so direction is in global FORWARD direction
	//	2) store the rotation
	//	3) rotate the pixelCoord vector by opposite of found rotation (60 back to global becomes -60 to new)
	//	4) add rotated pixelCoord to renderPlaneCenter 


	//get the rotation matrix that maps FORWARD vector to the unit direction vector
	Vec3 v = Primitive::Vec3Cross(Primitive::FORWARD, unitDirection);
	//float s = Primitive::Vec3Length(v);
	float c = Primitive::Vec3Dot(Primitive::FORWARD, unitDirection);

	if(c == 0.0) {
		std::cout << "Can't do that..." << std::endl;
		return Ray(Vec3(), Vec3(), 0);
	}

	float a = 1 / (1 + c);

	float varray[9] = { 0  , -v.z,  v.y,
						v.z,  0  , -v.x,
					   -v.y,  v.x,  0   };

	Mat3x3 Vx(varray);

	Mat3x3 R = Primitive::I + Vx + (Vx * Vx) * a;

	//multiply rotation matrix by pixelCoords unit vector so pixelCoords points in right direction
	//then add magnitude back into vector
	Vec3 pixelCoordsTranslated = (R * pixelCoordsNormal) * pixelCoordsMagnitude;

	//add updated pixel coords to center of render plane to get the final position of where to cast ray through
	Vec3 pixelCoordsOnRenderPlane = pixelCoordsTranslated + renderPlaneCenter;

	std::cout << "( 0, " << xNorm << ", " << yNorm << " ) ... ";
	std::cout << "( " << pixelCoordsOnRenderPlane.x << ", " << pixelCoordsOnRenderPlane.y << ", " << pixelCoordsOnRenderPlane.z << " )" << std::endl;

	//Ray vector is in direction of camera position -> calculated pixel coordinate on render plane
	Ray ray(this->position, pixelCoordsOnRenderPlane, 100.0);

	*/

	Ray ray(this->position, pixelCoords + renderPlaneCenter);

	return ray;
}

