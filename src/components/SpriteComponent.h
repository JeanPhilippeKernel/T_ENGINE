#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "../IComponent.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Engine.h"
#include "TransformComponent.h"
#include "Animation.h"


namespace T_Engine
{
	namespace Component
	{
		class Animation;

		class SpriteComponent : public IComponent
		{
		public:
			explicit SpriteComponent(const char* asset_key, std::uint32_t number_of_animation_frame, std::uint32_t frame_animation, bool has_direction, bool is_fixed);
			virtual ~SpriteComponent() = default;


			const SDL_Rect&		source_rect()		const { return *m_source_rect; }
			const SDL_Rect&		destination_rect()	const { return *m_destination_rect; }
			const SDL_Texture&	texture()			const { return *m_texture; }

			void PlayAnimation(const char * name);

			void Initialize()				override;
			void Update(float delta_time)	override;
			void Render()					override;

		private:
			std::uint32_t									m_number_of_frame			{ 0 };
			std::uint32_t									m_frame_animation			{ 0 };
			bool											m_has_direction				{ false };
			bool											m_is_fixed					{ false };

			std::unique_ptr<SDL_Rect>						m_source_rect				{ nullptr };
			std::unique_ptr<SDL_Rect>						m_destination_rect			{ nullptr };
			const SDL_Texture*								m_texture					{ nullptr };
			const SDL_Surface*								m_surface					{ nullptr };
			const TransformComponent*						m_transform_component		{ nullptr };

			SDL_RendererFlip								m_renderer_flip				{ SDL_FLIP_NONE };

			std::map<const char*, std::vector<Animation>>	m_animations;
			std::pair<const char*, std::uint32_t>			m_current_animation;
			
			
			void PlayAnimation(std::pair<const char*, std::uint32_t>& animation);
		};
	}
}
