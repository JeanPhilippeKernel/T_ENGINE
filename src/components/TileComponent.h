#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <glm/glm.hpp>

#include "../IComponent.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Engine.h"


namespace T_Engine
{
	namespace Component
	{
		class TileComponent : public IComponent
		{
		public:
			TileComponent(const char *  asset_key, int source_rect_x, int source_rect_y, int x, int y, int tile_size, int tile_scale);
			~TileComponent() = default;

			void Initialize()				override;
			void Update(float delta_time)	override;
			void Render()					override;

			glm::vec2	position() const { return m_position; }
			void		position(int x, int y) 
			{ 
				m_position.x = x;
				m_position.y = y;
			}

		private:
			const SDL_Texture*			m_texture			{ nullptr };
			std::unique_ptr<SDL_Rect>	m_source_rect		{ nullptr };
			std::unique_ptr<SDL_Rect>	m_destination_rect	{ nullptr };
			SDL_RendererFlip			m_renderer_flip		{ SDL_FLIP_NONE };
			glm::vec2					m_position;
		};
	}
}