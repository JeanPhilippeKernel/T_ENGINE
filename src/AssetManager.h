#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

#include "EntityManager.h"

namespace T_Engine
{

	class AssetManager 
	{
	public:
		explicit AssetManager(const EntityManager& entity_manager) 
			:m_entity_manager(entity_manager)
		{}
		~AssetManager();

		void				AddTexture(const char* asset_key, const char * file_path);
		const SDL_Texture*	GetTexture(const char* asset_key);
		const SDL_Surface*	GetSurface(const char* asset_key);



		void				AddFont(const char* asset_key, const char* file_path, size_t point_size);
		const TTF_Font*		GetFont(const char* asset_key);

	private:
		const EntityManager&				m_entity_manager;
		std::map<const char*, SDL_Texture*> m_texture_collection;
		std::map<const char*, SDL_Surface*> m_surface_collection;
		std::map<const char*, TTF_Font*>	m_font_collection;
	};
}
