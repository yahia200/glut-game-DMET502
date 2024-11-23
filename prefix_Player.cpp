#include "prefix_Player.h"

Player::Player()
{
	speed = 0.1;
	camera.at = Vector(0, 0, 0);
}

Player::Player(Vector pos, Vector hit)
{
	position = pos;
	camera.at = pos;
	hit_box = hit;
	speed = 0.1;
}

void Player::move(Vector dir)
{
	// Calculate the direction vector based on the player's rotation
	float rad = rotation.y * (3.14 / 180.0); // Convert rotation to radians
	Vector direction;
	direction.x = dir.x * cos(rad) + dir.z * sin(rad);
	direction.z = dir.z * cos(rad) - dir.x * sin(rad);
	direction.y = 0;

	if (dir.y > 0 && !is_jumping)
	{
		y_accel = jump_force;
		is_jumping = true;
	}

	position = position + direction * speed;
	camera.eye = camera.eye + direction * speed;

	printf("position: %f %f %f\n", position.x, position.y, position.z);
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
}

void Player::rotate(Vector dir)
{
	rotation += dir * 57.3;
	camera.rotate(dir);
}
