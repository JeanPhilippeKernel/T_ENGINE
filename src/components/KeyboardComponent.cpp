#pragma once
#include "KeyboardComponent.h"
#include "../EngineConstant.h"

namespace T_Engine
{
	namespace Component
	{

		KeyboardComponent::KeyboardComponent(const char* up_key, const char* right_key, const char* down_key, const char* left_key, const char* shoot_key)
		{
			m_up_key	= GetKeyFromName(up_key);
			m_right_key = GetKeyFromName(right_key);
			m_down_key	= GetKeyFromName(down_key);
			m_left_key	= GetKeyFromName(left_key);
			m_shoot_key = GetKeyFromName(shoot_key);
		}

		void KeyboardComponent::Initialize()
		{
			if (Owner_ptr)
			{
				m_transform_component	= const_cast<TransformComponent*>(Owner_ptr->GetComponent<TransformComponent>());
				m_sprite_component		= const_cast<SpriteComponent*>(Owner_ptr->GetComponent<SpriteComponent>());
			}
		}

		void KeyboardComponent::Update(float delta_time)
		{
			if (Engine::Event->type == SDL_KEYDOWN) 
			{
				if(Engine::Event->key.keysym.sym == m_up_key) 
				{
					m_transform_component->velocity(glm::vec2(0, -70));
					m_sprite_component->PlayAnimation(EngineConstant::Animation::UP_ANIMATION);
				}
				
				if(Engine::Event->key.keysym.sym == m_down_key) 
				{
					m_transform_component->velocity(glm::vec2(0, 70));
					m_sprite_component->PlayAnimation(EngineConstant::Animation::DOWN_ANIMATION);
				}
				
				if(Engine::Event->key.keysym.sym == m_left_key) 
				{
					m_transform_component->velocity(glm::vec2(-70, 0));
					m_sprite_component->PlayAnimation(EngineConstant::Animation::LEFT_ANIMATION);
				}
				
				if(Engine::Event->key.keysym.sym == m_right_key) 
				{
					m_transform_component->velocity(glm::vec2(70, 0));
					m_sprite_component->PlayAnimation(EngineConstant::Animation::RIGHT_ANIMATION);
				}

				if (Engine::Event->key.keysym.sym == m_shoot_key)
				{
					  //ToDo: ...
				}

			}

			if (Engine::Event->type == SDL_KEYUP)
			{
				if (Engine::Event->key.keysym.sym == m_up_key)
				{
					m_transform_component->velocity(
						glm::vec2(m_transform_component->velocity().x, 0)
					);
				}

				if (Engine::Event->key.keysym.sym == m_down_key)
				{
					m_transform_component->velocity(
						glm::vec2(m_transform_component->velocity().x, 0)
					);
				}

				if (Engine::Event->key.keysym.sym == m_left_key)
				{
					m_transform_component->velocity(
						glm::vec2(0, m_transform_component->velocity().y)
					);
				}

				if (Engine::Event->key.keysym.sym == m_right_key)
				{
					m_transform_component->velocity(
						glm::vec2(0, m_transform_component->velocity().y)
					);
				}

				if (Engine::Event->key.keysym.sym == m_shoot_key)
				{
					//ToDo: ...
				}

			}

		}

		void KeyboardComponent::Render() {}

	}
}