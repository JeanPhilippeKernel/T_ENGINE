#pragma once
#include "FontManager.h"
 
namespace T_Engine
{
	TTF_Font* FontManager::LoadFont(const char* filename, size_t point_size)
	{
		TTF_Font* font = TTF_OpenFont(filename, point_size);
		if (font) return font;
		return nullptr;
	}

	void FontManager::RenderFont(
		const SDL_Renderer* renderer, const SDL_Texture* texture,
		const SDL_Rect* destination_rec
	)
	{
		SDL_RenderCopy(
			const_cast<SDL_Renderer*>(renderer), const_cast<SDL_Texture*>(texture),
			NULL, destination_rec
		);
	}
}