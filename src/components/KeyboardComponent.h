#pragma once

#include <string>

#include "../IComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "../Engine.h"

namespace T_Engine
{
	namespace Component
	{
		class KeyboardComponent : public IComponent
		{
		public:
			KeyboardComponent(const char* up_key, const char* right_key, const char* down_key, const char* left_key, const char* shoot_key);
			~KeyboardComponent() = default;

			void Initialize()				override;
			void Update(float delta_time)	override;
			void Render()					override;

		private:
			SDL_Keycode				m_up_key	{};
			SDL_Keycode				m_down_key	{};
			SDL_Keycode				m_left_key	{};
			SDL_Keycode				m_right_key	{};
			SDL_Keycode				m_shoot_key	{};

			TransformComponent*		m_transform_component	{ nullptr };
			SpriteComponent*		m_sprite_component		{ nullptr }; 

			SDL_Keycode GetKeyFromName(const char* key_name)
			{
				auto key = SDL_GetKeyFromName(key_name);
				if (key == SDLK_UNKNOWN)
					std::cerr << key_name << " is unknown" << std::endl;

				return key;
			}
		};
	}
}