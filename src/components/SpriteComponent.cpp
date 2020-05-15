#pragma once
#include "SpriteComponent.h"
#include "../EngineConstant.h"

namespace T_Engine
{
	namespace Component
	{
		SpriteComponent::SpriteComponent(const char* asset_key, std::uint32_t number_of_animation_frame, std::uint32_t frame_animation, bool has_direction, bool is_fixed)
			:m_number_of_frame(number_of_animation_frame), m_frame_animation(frame_animation), m_has_direction(has_direction), m_is_fixed(is_fixed)
		{
			m_texture			= Engine::AssetManager->GetTexture(asset_key);
			m_surface			= Engine::AssetManager->GetSurface(asset_key);
			m_source_rect		= std::make_unique<SDL_Rect>();
			m_destination_rect	= std::make_unique<SDL_Rect>();
		}

		void SpriteComponent::Initialize()
		{

			if (Owner_ptr)
			{
				m_transform_component	= Owner_ptr->GetComponent<TransformComponent>();

				m_source_rect->x		= 0;
				m_source_rect->y		= 0;
				m_source_rect->w		= static_cast<int>(m_transform_component->width());
				m_source_rect->h		= static_cast<int>(m_transform_component->height());

				m_destination_rect->x	= static_cast<int>(m_transform_component->position().x);
				m_destination_rect->y	= static_cast<int>(m_transform_component->position().y);
				m_destination_rect->w	= static_cast<int>(m_transform_component->width() * m_transform_component->scale().x);
				m_destination_rect->h	= static_cast<int>(m_transform_component->height() * m_transform_component->scale().y);

			}

			if (m_has_direction)
			{
				Animation down_animation_one	{ 0, 0, 0, m_source_rect->w,  m_source_rect->h };
				Animation down_animation_two	{ 0, m_source_rect->w, 0, m_source_rect->w,  m_source_rect->h };
				
				Animation right_animation_one	{ 1, 0, m_source_rect->h, m_source_rect->w,  m_source_rect->h };
				Animation right_animation_two	{ 1, m_source_rect->w, m_source_rect->h, m_source_rect->w,  m_source_rect->h };
				
				Animation left_animation_one	{ 2, 0, 2 * m_source_rect->h, m_source_rect->w,  m_source_rect->h };
				Animation left_animation_two	{ 2, m_source_rect->w, 2 * m_source_rect->h, m_source_rect->w,  m_source_rect->h };
				
				Animation up_animation_one		{ 3, 0, 3 * m_source_rect->h, m_source_rect->w,  m_source_rect->h };
				Animation up_animation_two		{ 3, m_source_rect->w, 3 * m_source_rect->h, m_source_rect->w,  m_source_rect->h };

				m_animations.emplace(EngineConstant::Animation::DOWN_ANIMATION,		std::vector<Animation>{ down_animation_one, down_animation_two });
				m_animations.emplace(EngineConstant::Animation::LEFT_ANIMATION,		std::vector<Animation>{ left_animation_one, left_animation_two });
				m_animations.emplace(EngineConstant::Animation::RIGHT_ANIMATION,	std::vector<Animation>{ right_animation_one, right_animation_two });
				m_animations.emplace(EngineConstant::Animation::UP_ANIMATION,		std::vector<Animation>{ up_animation_one, up_animation_two });
				
				m_current_animation = std::make_pair(EngineConstant::Animation::DOWN_ANIMATION, 0);
			}
			else
			{

				std::vector<int> x_range;
				std::vector<int> y_range;

				for (size_t x = 0; x < m_number_of_frame; ++x)
					x_range.push_back(x);
				for (size_t y = 0; y < (m_surface->h / m_transform_component->height()); ++y)
					y_range.push_back(y);


				//single animation
				for (int y : y_range) 
				{
					for (int x : x_range)
						m_animations[EngineConstant::Animation::SINGLE_ANIMATION].push_back(Animation{ 0, x * m_source_rect->w, y * m_source_rect->h, m_source_rect->w, m_source_rect->h });
				}

				m_current_animation = std::make_pair(EngineConstant::Animation::SINGLE_ANIMATION, 0);
			}
		}

		void SpriteComponent::PlayAnimation(const char * animation_name)
		{
			m_current_animation.first	= animation_name;
			m_current_animation.second	= 0;
		}


		void SpriteComponent::PlayAnimation(std::pair<const char*, std::uint32_t>& animation)
		{
			auto animations				= m_animations[animation.first];
			*m_source_rect				= animations[animation.second].target_rect();
			m_current_animation.second	= static_cast<int>(SDL_GetTicks() / m_frame_animation) % m_number_of_frame;
		}

		void SpriteComponent::Update(float delta_time)
		{
			PlayAnimation(m_current_animation);

			if (!m_is_fixed) 
			{
				m_destination_rect->x = static_cast<int>(m_transform_component->position().x) - Engine::Camera->x;
				m_destination_rect->y = static_cast<int>(m_transform_component->position().y) - Engine::Camera->y;
				m_destination_rect->w = static_cast<int>(m_transform_component->width()		* m_transform_component->scale().x);
				m_destination_rect->h = static_cast<int>(m_transform_component->height()	* m_transform_component->scale().y);
			}

		}

		void SpriteComponent::Render()
		{
			TextureManager::RenderTexture(
				Engine::Renderer, m_texture, m_source_rect.get(), m_destination_rect.get(), 
				m_renderer_flip
			);
		}

	}
}
