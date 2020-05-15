#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../IComponent.h"
#include "TransformComponent.h"
#include "../Engine.h"


namespace T_Engine
{
	namespace Component
	{
		class ColliderComponent : public IComponent
		{
		public:
			explicit ColliderComponent(
				bool show_collision_rect = true, 
				std::uint8_t red = 255, std::uint8_t green = 255, std::uint8_t blue = 255
			);

			void Initialize()				override;
			void Update(float delta_time)	override;
			void Render()					override;

			const SDL_Rect& collision_rect() const { return *m_collision_rect; }


		private:
			std::unique_ptr<SDL_Rect> m_collision_rect		{ nullptr };

			bool m_show_collision_rect						{ true };
			std::uint8_t m_red_color						{ 0 };
			std::uint8_t m_green_color						{ 0 };
			std::uint8_t m_blue_color						{ 0 };

			const TransformComponent* m_transform_component	{ nullptr };
		};
	}
}