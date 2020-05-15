#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


namespace T_Engine
{
	class TextureManager
	{
	public:
		TextureManager() = delete;

		static SDL_Texture*	LoadTexture(const char* filename);
		static SDL_Surface*	LoadSurface(const char* filename);
		static void			RenderTexture(
									const SDL_Renderer* renderer, const SDL_Texture* texture,
									const SDL_Rect* rect_source, const SDL_Rect* dest_source,
									SDL_RendererFlip renderer_flip
								);
	private:
	};
}
