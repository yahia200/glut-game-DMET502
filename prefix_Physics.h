#pragma once
#include "prefix_Entity.h"
class Physics
{
public:
	Physics();
	bool is_colliding(Entity e1, Entity e2);
};

