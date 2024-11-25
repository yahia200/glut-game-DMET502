#pragma once
#include "prefix_Vector.h"
#include "prefix_Entity.h" 
#include "prefix_Camera.h"

#define g -0.6

class Player : public Entity
{
public:
	Player();
	Player(Vector pos, Vector hit);
	float speed = 0.2;
	float jump_force = 1.3, y_accel = g;
	bool is_jumping;
	int collectables[collectable_types_count];
	void move(Vector dir);
	Camera camera;
	void rotate(Vector dir);
	void update();
	void jump();

};


