#include "prefix_Collectable.h"

Collectable::Collectable()
{
}

Collectable::Collectable(Vector pos, Vector hit, CollectableType type)
{
	position = pos;
	hit_box = hit;
	this->type = egg;
}