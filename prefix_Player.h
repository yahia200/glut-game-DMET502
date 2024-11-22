#pragma once
#include "prefix_Vector.h"
#include "prefix_Entity.h" 
#include "prefix_Camera.h"
class Player : public Entity
{
public:
	Player();
	Player(Vector pos, Vector hit);
	float speed, camera_dis;
	void move(Vector dir);
	Camera camera;
	void update();
};

