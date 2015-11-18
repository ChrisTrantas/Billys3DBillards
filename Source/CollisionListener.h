#pragma once
#include "Component.hpp"
#include "Collider.hpp"

class CollisionListener :
	public Component
{
public:
	CollisionListener();
	~CollisionListener();

	void notify(Collider* listenee);	// Called upon by the listenee
};

