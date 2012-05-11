#include "Camera.h"

#define SQR(x) (x*x)

#define NULL_VECTOR Vector3(0.0f, 0.0f, 0.0f)

Vector3 vector(float x, float y, float z) {
	Vector3 tmp(x, y, z);
	return tmp;
}

/***************************************************************************************/

Camera::Camera() {
	//Init with standard OGL values:
	position = Vector3(0.0, 0.0, 0.0);
	viewDir = Vector3(0.0, 0.0, -1.0);
	rightVector = Vector3(1.0, 0.0, 0.0);
	upVector = Vector3(0.0, 1.0, 0.0);

	//Only to be sure:
	rotatedX = rotatedY = rotatedZ = 0.0;
}

void Camera::move(Vector3 direction) {
	position = position + direction;
}

void Camera::rotateX(float angle) {
	rotatedX += angle;
	
	//Rotate viewdir around the right vector:
	viewDir = Vector3(viewDir * cos(angle * M_PI / 180)	+ upVector * sin(angle * M_PI / 180));
	viewDir.normalize();

	//now compute the new UpVector (by cross product)
	upVector = viewDir^rightVector * -1;
}

void Camera::rotateY(float angle) {
	rotatedY += angle;
	
	//Rotate viewdir around the up vector:
	viewDir = viewDir * cos(angle * M_PI / 180)	- rightVector * sin(angle * M_PI / 180);
	viewDir.normalize();

	//now compute the new RightVector (by cross product)
	rightVector = viewDir^upVector;
}

void Camera::rotateZ(float angle) {
	rotatedZ += angle;
	
	//Rotate viewdir around the right vector:
	rightVector = rightVector * cos(angle * M_PI / 180) + upVector * sin(angle * M_PI / 180);
	rightVector.normalize();

	//now compute the new UpVector (by cross product)
	upVector = viewDir^rightVector * -1;
}

void Camera::render() {
	//The point at which the camera looks:
	Vector3 viewPoint = position + viewDir;

	//as we know the up vector, we can easily use gluLookAt:
	gluLookAt(position.x, position.y, position.z,
				viewPoint.x, viewPoint.y, viewPoint.z,
				upVector.x, upVector.y, upVector.z);

}

void Camera::moveForward(float distance) {
	position = position + (viewDir * -distance);
}

void Camera::strafeRight(float distance) {
	position = position + (rightVector * distance);
}

void Camera::moveUpward(float distance) {
	position = position + (upVector * distance);
}