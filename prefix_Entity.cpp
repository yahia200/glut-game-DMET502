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

void Entity::draw(float time , char p)
{
	float amplitude = 1.0f; // Maximum height displacement
	float frequency = 1.0f; // Speed of oscillation

	float verticalTranslation = amplitude * sin(frequency * time); // Up and down motion

	
	glPushMatrix();
	glTranslatef(position.x, position.y+hit_box.y/2, position.z);
	glScaled(scale.x, scale.y, scale.z);
	glRotated(rotation.y, 0, 1, 0);
	glRotated(rotation.x, 1, 0, 0);
	glRotated(rotation.z, 0, 0, 1);
	if (p == 'o') {
		glTranslatef(0.0f, verticalTranslation, 0.0f);  // Move up/down along Y-axis

		// Apply rotation around the Y-axis
		float rotationAngle = time * 45.0f;  // Rotate 45 degrees per second
		glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);  // Rotate around Y-axis
	}
	model.Draw();
	glPopMatrix();
}

void Entity::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y + hit_box.y / 2, position.z);
	glScaled(scale.x, scale.y, scale.z);
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


