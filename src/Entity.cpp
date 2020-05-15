#include <SDL2/SDL.h>

#include "Entity.h"
#include "components/TransformComponent.h"
#include "components/TileComponent.h"
#include "components/ColliderComponent.h"
#include "Engine.h"

using namespace T_Engine::Component;

namespace T_Engine
{

	void Entity::_VerifyCollision() const
	{
		auto collection = m_entity_manager.GetEntityByLayer(2, EngineConstant::Layer::PLAYER, EngineConstant::Layer::ENEMY);
		for (auto& item : collection)
		{
			if (this !=  item 
				&& item->HasComponent<ColliderComponent>()
				&& this->HasComponent<ColliderComponent>())
			{
				 if(Engine::CollisionManager->HasCollide(*this, *item))
					 if(m_collision_callback) m_collision_callback(*this, *item);

			}
		}
	}

	void Entity::AttachCamera(const std::shared_ptr<SDL_Rect>& camera)
	{
		m_attached_camera		= camera;
		m_has_camera_attached	= true;
	}


	void Entity::Update(float delta_time)
	{
		for (const auto& item : m_components)
			item->Update(delta_time);

		if (m_has_camera_attached)
		{
			if (m_layer == EngineConstant::Layer::PLAYER)
			{						  
				const auto transform = GetComponent<TransformComponent>();
				m_attached_camera->x = glm::clamp<int>(transform->position().x - (EngineConstant::WINDOW_WIDTH / 2), 0, m_attached_camera->w);
				m_attached_camera->y = glm::clamp<int>(transform->position().y - (EngineConstant::WINDOW_HEIGHT / 2), 0, m_attached_camera->h);

				std::cout << "Cam X : " << m_attached_camera->x << std::endl;
				std::cout << "Cam Y : " << m_attached_camera->y << std::endl;

			}
		}


		_VerifyCollision();
	}

	void Entity::Render()
	{
		for (const auto& item : m_components)
			item->Render();
	}

}
