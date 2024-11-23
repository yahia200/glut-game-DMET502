#include "prefix_Entity.h"

Entity::Entity()
{
	position = Vector(0, 0, 0);
	hit_box = Vector(0, 0, 0);
	model = Model_3DS();
}



Entity::Entity(Vector pos, Vector hit)
{
	position = pos;
	hit_box = hit;
}

void Entity::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y+hit_box.y/2, position.z);
	glRotated(rotation.y, 0, 1, 0);
	glRotated(rotation.x, 1, 0, 0);
	glRotated(rotation.z, 0, 0, 1);
	model.Draw();
	glPopMatrix();
}

void Entity::load_model(char* name)
{
	model.Load(name);
}

void Entity::rotate(Vector dir)
{
	rotation += dir;
	printf("Rotation: %f %f %f\n", rotation.x, rotation.y, rotation.z);
}


