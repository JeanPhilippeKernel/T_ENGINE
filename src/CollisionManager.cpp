#include "CollisionManager.h"
#include "components/ColliderComponent.h"
using namespace T_Engine::Component;

namespace T_Engine
{
	bool CollisionManager::HasCollide(const Entity& left, const Entity& right) const
	{
		auto left_collider_compnt	= left.GetComponent<ColliderComponent>();
		auto right_collider_compnt	= right.GetComponent<ColliderComponent>();

		auto left_inner_rect	= left_collider_compnt->collision_rect();
		auto right_inner_rect	= right_collider_compnt->collision_rect();

		return (
			(left_inner_rect.x + left_inner_rect.w) >= right_inner_rect.x &&
			(left_inner_rect.y + left_inner_rect.h) >= right_inner_rect.y &&
			(right_inner_rect.x + right_inner_rect.w) >= left_inner_rect.x &&
			(right_inner_rect.y + right_inner_rect.h) >= left_inner_rect.y
			);
	}

}