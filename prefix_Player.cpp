#include "prefix_Player.h"

Player::Player()
{
	speed = 0.1;
	camera_dis = 30;
	camera.at = Vector(0, 0, 0);
}

Player::Player(Vector pos, Vector hit)
{
	position = pos;
	camera.at = pos;
	hit_box = hit;
	speed = 0.1;
	camera_dis = 30;
}

void Player::move(Vector dir)
{
	position = position + !dir * speed;
	camera.eye = camera.eye + !dir * speed;
}

void Player::update()
{
	camera.at = position;
		camera.setCamera();
}

void Player::rotate(Vector dir)
{
	rotation += dir * 57.3;
	camera.rotate(dir);
}
