#pragma once

#include "TileComponent.h"

namespace T_Engine
{
	namespace Component 
	{

		TileComponent::TileComponent(const char* asset_key, int source_rect_x, int source_rect_y, int x, int y, int tile_size, int tile_scale)
		{
			m_source_rect			= std::make_unique<SDL_Rect>();
			m_destination_rect		= std::make_unique<SDL_Rect>();
			
			m_texture				= Engine::AssetManager->GetTexture(asset_key);

			m_source_rect->x		= source_rect_x;
			m_source_rect->y		= source_rect_y;
			m_source_rect->w		= tile_size;
			m_source_rect->h		= tile_size;

			m_destination_rect->x	= x;
			m_destination_rect->y	= y;
			m_destination_rect->w	= tile_size * tile_scale;
			m_destination_rect->h	= tile_size * tile_scale;

			m_position.x			= x;
			m_position.y			= y;
		}

		void TileComponent::Initialize()
		{
		}

		void TileComponent::Update(float delta_time)
		{
			if (Engine::Camera != nullptr)
			{
				m_destination_rect->x = m_position.x - Engine::Camera->x;
				m_destination_rect->y = m_position.y - Engine::Camera->y;
				
				if (m_destination_rect->x > Engine::Camera->w) m_destination_rect->x = Engine::Camera->w;
				if (m_destination_rect->y > Engine::Camera->h) m_destination_rect->y = Engine::Camera->h;
			}
		}

		void TileComponent::Render()
		{
			TextureManager::RenderTexture(Engine::Renderer, m_texture, m_source_rect.get(), m_destination_rect.get(), m_renderer_flip);
		}

	}
}