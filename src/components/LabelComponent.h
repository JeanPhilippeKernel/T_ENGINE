#pragma once
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "../IComponent.h"
#include "TransformComponent.h"

namespace T_Engine
{
	namespace Component
	{
		class LabelComponent : public IComponent
		{
		public:
			explicit LabelComponent(
				const char* asset_key, const char* label,
				std::uint8_t red, std::uint8_t green, std::uint8_t blue
			);

			void Initialize()				override;
			void Update(float delta_time)	override;
			void Render()					override;


		private:
			std::string		m_label							{};
			SDL_Color		m_color							{};
			SDL_Rect		m_destination					{};

			const TransformComponent* m_tranform_component	{ nullptr };
			const TTF_Font* m_font							{ nullptr };
		};
	}
}