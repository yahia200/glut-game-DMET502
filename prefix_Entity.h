#pragma once
#include "prefix_Vector.h"
#include "Model_3DS.h"

typedef enum CollectableType
{
	egg = 0,

	collectable_types_count
} CollectableType;


class Entity
{
public:
	Vector position, hit_box, rotation, scale = Vector(1,1,1);
	Model_3DS model;
	Entity();
	Entity(Vector pos, Vector hit);
	void load_model(char *name);
	void draw();
	void rotate(Vector dir);
};

