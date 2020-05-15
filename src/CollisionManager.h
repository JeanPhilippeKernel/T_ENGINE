#pragma once
#include "Entity.h"

namespace T_Engine 
{
	class Entity;
	class CollisionManager
	{
	public:
		CollisionManager()	= default;
		~CollisionManager() = default;

		bool HasCollide(const Entity& left, const Entity& right) const;
	};
}
