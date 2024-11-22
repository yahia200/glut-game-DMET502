#pragma once
#include "prefix_Vector.h"
#include "math.h"
#include <glut.h>
class Camera
{
public:
	Vector eye, at, up;
	float cameraZoom;
	Camera();
	void move(Vector v);
	void zoom(int x, int y, int h);
	void setCamera();
	void rotate(Vector v);
};

