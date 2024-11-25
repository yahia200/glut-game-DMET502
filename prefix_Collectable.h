#pragma once
#include "prefix_Entity.h"


class Collectable : public Entity
{
public:
	Collectable();
	Collectable(Vector pos, Vector hit, CollectableType type);
	CollectableType type;
	bool collected = false;
};

