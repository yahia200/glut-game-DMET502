#include "prefix_Physics.h"

Physics::Physics()
{
	// Initialize the physics engine
	// ...
}

bool Physics::is_colliding(Entity e1, Entity e2)
{	
		Vector e1_min = e1.position - e1.hit_box;
		Vector e1_max = e1.position + e1.hit_box;

		Vector e2_min = e2.position - e2.hit_box;
		Vector e2_max = e2.position + e2.hit_box;

		if (e1_min.x < e2_max.x && e1_max.x > e2_min.x &&
			e1_min.y < e2_max.y && e1_max.y > e2_min.y &&
			e1_min.z < e2_max.z && e1_max.z > e2_min.z)
		{
			return true;
		}
		return false;
	
}

