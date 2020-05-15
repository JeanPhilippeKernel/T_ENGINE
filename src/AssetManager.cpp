#include <algorithm>

#include "AssetManager.h"
#include "TextureManager.h"
#include "FontManager.h"

namespace T_Engine
{

	AssetManager::~AssetManager()
	{
		for (auto it = std::begin(m_surface_collection); it != std::end(m_surface_collection); ++it)
			SDL_FreeSurface(it->second);

	}

	void AssetManager::AddTexture(const char* asset_key, const char* file_path)
	{
		auto it		= m_texture_collection.find(asset_key);
		auto it_2	= m_surface_collection.find(asset_key);
		
		if (it != std::end(m_texture_collection))
		{
			it->second		= TextureManager::LoadTexture(file_path);
			it_2->second	= TextureManager::LoadSurface(file_path);
		}
		else
		{
			m_texture_collection.emplace(asset_key, TextureManager::LoadTexture(file_path));
			m_surface_collection.emplace(asset_key, TextureManager::LoadSurface(file_path));
		}

	}

	const SDL_Texture* AssetManager::GetTexture(const char* asset_key)
	{
		auto it = std::find_if(
				std::begin(m_texture_collection), std::end(m_texture_collection),
				[asset_key](const auto& x) { return strcmp(x.first, asset_key) == 0; 
			});

		if (it != std::end(m_texture_collection))
			return it->second;
		
		return nullptr;
	}

	const SDL_Surface* AssetManager::GetSurface(const char* asset_key)
	{
		auto it = m_surface_collection.find(asset_key);
		if (it != std::end(m_surface_collection))
			return it->second;

		return nullptr;
	}


	void AssetManager::AddFont(const char* asset_key, const char* file_path, size_t point_size)
	{
		auto it = m_font_collection.find(asset_key);
		if (it != std::end(m_font_collection))
		{
			it->second = FontManager::LoadFont(file_path, point_size);
		}

		m_font_collection.emplace(asset_key, FontManager::LoadFont(file_path, point_size));
	}

	const TTF_Font* AssetManager::GetFont(const char* asset_key)
	{
		auto  it = m_font_collection.find(asset_key);
		if (it != std::end(m_font_collection))
			return it->second;

		return nullptr;
	}

}