#pragma once
#include "LabelComponent.h"
#include "../Engine.h"
#include "../FontManager.h"

namespace T_Engine
{
	namespace Component
	{
		LabelComponent::LabelComponent(const char* asset_key, const char* label,
			std::uint8_t red, std::uint8_t green, std::uint8_t blue
		)	: m_label(label)
		{
			m_font	= Engine::AssetManager->GetFont(asset_key);
			m_color = { red, green, blue, SDL_ALPHA_OPAQUE };
		}


		void LabelComponent::Initialize()
		{
			if (Owner_ptr && Owner_ptr->HasComponent<TransformComponent>())
			{
				m_tranform_component = Owner_ptr->GetComponent<TransformComponent>();
				m_destination.x = m_tranform_component->position().x;
				m_destination.y = m_tranform_component->position().y;
				m_destination.w = m_tranform_component->width();
				m_destination.h = m_tranform_component->height();
			}
		}

		void LabelComponent::Update(float delta_time)
		{
			m_destination.x = m_tranform_component->position().x;
			m_destination.y = m_tranform_component->position().y;
			m_destination.w = m_tranform_component->width();
			m_destination.h = m_tranform_component->height();
		}
		
		void LabelComponent::Render()
		{
			auto surface = TTF_RenderText_Blended(const_cast<TTF_Font*>(m_font), m_label.c_str(), m_color);
			if (surface)
			{
				auto texture = SDL_CreateTextureFromSurface(Engine::Renderer, surface);
				FontManager::RenderFont(Engine::Renderer, texture, &m_destination);
		
				SDL_FreeSurface(surface);
				SDL_DestroyTexture(texture);
			}
		}
	}
}