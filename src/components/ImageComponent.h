#pragma once
#include <memory>
#include <SDL2/SDL.h>

#include "../IComponent.h"
#include "TransformComponent.h"
#include "../Engine.h"
#include "../TextureManager.h"

namespace T_Engine
{
	namespace Component
	{
		class ImageComponent : public IComponent
		{
		public:
			explicit ImageComponent(const char* asset_key);
			virtual ~ImageComponent() = default;


			void Initialize() override;
			void Update(float delta_time) override;
			void Render() override;


		private:
			std::unique_ptr<SDL_Rect>	m_source_rect;
			std::unique_ptr<SDL_Rect>	m_destination_rect;
							  
			const SDL_Texture*			m_texture		{ nullptr };
			const TransformComponent*	m_transform		{ nullptr };
			SDL_RendererFlip			m_renderer_flip	{ SDL_FLIP_NONE };
		};
	}
}