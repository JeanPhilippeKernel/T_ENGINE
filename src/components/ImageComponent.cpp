#pragma once
#include "ImageComponent.h"


namespace T_Engine
{
	namespace Component
	{
		ImageComponent::ImageComponent(const char* asset_key)
		{
			m_texture			= Engine::AssetManager->GetTexture(asset_key);
			m_source_rect		= std::make_unique<SDL_Rect>();
			m_destination_rect	= std::make_unique<SDL_Rect>();
		}


		void ImageComponent::Initialize()
		{
			if (Owner_ptr)
			{
				m_transform = Owner_ptr->GetComponent<TransformComponent>();

				m_source_rect->x = 0;
				m_source_rect->y = 0;
				m_source_rect->w = m_transform->width();
				m_source_rect->h = m_transform->height();
			}
		}

		void ImageComponent::Update(float delta_time)
		{
			m_destination_rect->x = static_cast<int>(m_transform->position().x);
			m_destination_rect->y = static_cast<int>(m_transform->position().y);
			m_destination_rect->w = static_cast<int>(m_transform->width()	* m_transform->scale().x);
			m_destination_rect->h = static_cast<int>(m_transform->height()	* m_transform->scale().y);
		}

		void ImageComponent::Render()
		{
			TextureManager::RenderTexture(Engine::Renderer, m_texture, m_source_rect.get(), m_destination_rect.get(), m_renderer_flip);
		}
	}
}