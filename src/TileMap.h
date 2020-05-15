#pragma once

#include <string>
#include "EntityManager.h"


namespace T_Engine
{
	class TileMap
	{
	public:
		TileMap(EntityManager& entity_manager, const char * texture_id, int scale, int tile_size);
		~TileMap() = default;

		void LoadMap(const char* filename, int map_size_x, int map_size_y);
		void AddTile(int source_x, int source_y, int x, int y);

	private:
		EntityManager& m_entity_manager;

		std::string m_texture_id	{};
		int m_scale					{ 0 };
		int m_tile_size				{ 0 };
	};

}