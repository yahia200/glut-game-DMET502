#include "prefix_Player.h"

Player::Player()
{
	
	camera.at = Vector(0, 0, 0);
}

Player::Player(Vector pos, Vector hit)
{
	position = pos;
	camera.at = pos;
	hit_box = hit;
}

void Player::move(Vector dir)
{
	


	position = position + dir * speed;
	camera.eye = camera.eye + dir * speed;

	//printf("position: %f %f %f\n", position.x, position.y, position.z);
}

void Player::jump()
{
	if (!is_jumping)
	{
		y_accel = jump_force;
		is_jumping = true;
	}
}

void Player::update()
{
	y_accel += g*0.25;

	if (y_accel < g)
		y_accel = g;

	position.y += y_accel;
	
	if (position.y <= 0)
	{
		if(is_jumping)
			is_jumping = false;
		position.y = 0;
	}

	camera.eye.y = position.y;
	camera.at = position;
	camera.setCamera(position);

	for (int cc : collectables)
	{
		printf("%d\n", cc);
	}
}

void Player::rotate(Vector dir)
{
	rotation += dir * 57.3;
	camera.rotate(dir);
}
