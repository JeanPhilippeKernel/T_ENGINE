#pragma once
#include <SDL2/SDL_rect.h>

namespace T_Engine
{
	namespace Component
	{
		class Animation
		{
		public:
			Animation(std::uint32_t index, int target_x, int target_y, int target_w, int target_h)
				:m_index(index)
			{
				m_target_rect = { target_x, target_y, target_w, target_h };
			}
		
			const SDL_Rect& target_rect() const { return m_target_rect; }

		private:
			std::uint32_t	m_index{ 0 };
			SDL_Rect		m_target_rect;
		};
	}
}