#include	"ColliderComponent.h"

namespace T_Engine
{
	namespace Component 
	{
		ColliderComponent::ColliderComponent(bool show_collision_rect, std::uint8_t red, std::uint8_t green, std::uint8_t blue)
			:m_show_collision_rect(show_collision_rect), m_red_color(red), m_green_color(green), m_blue_color(blue)
		{
			m_collision_rect = std::make_unique<SDL_Rect>();
		}

		void ColliderComponent::Initialize() 
		{
		   if(Owner_ptr)
		   {
			   m_transform_component	= Owner_ptr->GetComponent<TransformComponent>();
			   m_collision_rect->x		= m_transform_component->position().x;
			   m_collision_rect->y		= m_transform_component->position().y;
			   m_collision_rect->w		= m_transform_component->width();
			   m_collision_rect->h		= m_transform_component->height();
		   }
		}

		void ColliderComponent::Update(float delta_time)
		{
			if (Owner_ptr->has_camera_attached())
			{
				m_collision_rect->x	= m_transform_component->position().x - Engine::Camera->x;
				m_collision_rect->y	= m_transform_component->position().y - Engine::Camera->y;
			}
			else
			{
				m_collision_rect->x = m_transform_component->position().x;
				m_collision_rect->y = m_transform_component->position().y;
			}
			m_collision_rect->w	= m_transform_component->width();
			m_collision_rect->h	= m_transform_component->height();

		}

		void ColliderComponent::Render()
		{
			if (m_show_collision_rect)
			{
				SDL_SetRenderDrawColor(Engine::Renderer, m_red_color, m_green_color, m_blue_color, SDL_ALPHA_TRANSPARENT);
				SDL_RenderDrawRect(Engine::Renderer, m_collision_rect.get());
			}	
		}

	}
}