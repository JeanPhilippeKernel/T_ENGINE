#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace T_Engine
{
	class FontManager 
	{
	public:
		FontManager() = delete;

		static 	TTF_Font*	LoadFont(const char* filename, size_t point_size);
		static	void		RenderFont(
									const SDL_Renderer* render, const SDL_Texture* texture,
									const SDL_Rect* destination_rec
								);

	};
}
