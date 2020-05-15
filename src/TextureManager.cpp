#include "TextureManager.h"
#include "Engine.h"

namespace T_Engine
{

	SDL_Texture* TextureManager::LoadTexture(const char* filename)
	{
		SDL_Surface* surface = IMG_Load(filename);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::Renderer, surface);
		if (texture != nullptr)
			SDL_FreeSurface(surface);

		return texture;
	}

	SDL_Surface* TextureManager::LoadSurface(const char* filename)
	{
		SDL_Surface* surface{ nullptr };
		surface = IMG_Load(filename);
		return surface;
	}


	void TextureManager::RenderTexture(
		const SDL_Renderer* renderer, const SDL_Texture* texture,
		const SDL_Rect* rect_source, const SDL_Rect* dest_source,
		SDL_RendererFlip renderer_flip
	)
	{
		SDL_RenderCopyEx(
			const_cast<SDL_Renderer*>(renderer), const_cast<SDL_Texture*>(texture),
			rect_source, dest_source, 0, NULL, renderer_flip
		);
	}
}