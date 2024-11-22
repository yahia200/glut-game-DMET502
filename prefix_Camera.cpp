#include "prefix_Camera.h"

Camera::Camera()
{
	eye = Vector(0, 0, 0);
	at = Vector(0, 0, 0);
	up = Vector(0, 0, 0);
	cameraZoom = 0;
}

void Camera::move(Vector v)
{
	eye += v;
}

void Camera::zoom(int x, int y, int h)
{
	y = h - y;

	if (cameraZoom - y > 0)
	{
		eye.x += -0.1;
		eye.z += -0.1;
	}
	else
	{
		eye.x += 0.1;
		eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(eye.x, eye.y, eye.z, at.x, at.y, at.z, up.x, up.y, up.z);	//Setup Camera with modified paramters
}

void Camera::setCamera()
{
	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(eye.x, eye.y, eye.z, at.x, at.y, at.z, up.x, up.y, up.z);	//Setup Camera with modified paramters
}

void Camera::rotate(Vector v)
{
	float lb = ~(eye - at);
	eye.x -= at.x;
	eye.z -= at.z;
	float newX = eye.x * cosf(v.y) + eye.z * sinf(v.y);
	float newZ = eye.x * -sinf(v.y) + eye.z * cosf(v.y);
	eye.x = newX;
	eye.z = newZ;
	eye.x += at.x;
	eye.z += at.z;

	Vector direction = eye - at;
	float currentDistance = ~direction;
	direction.x *= lb / currentDistance;
	direction.z *= lb / currentDistance;
	eye = at + direction;

	setCamera();

}