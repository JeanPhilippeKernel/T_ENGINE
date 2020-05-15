#include <fstream>
#include <iostream>

#include "TileMap.h"
#include "components/TileComponent.h"



using namespace T_Engine::Component;

namespace T_Engine
{
	TileMap::TileMap(EntityManager& entity_manager, const char* texture_id, int scale, int tile_size)
		:m_texture_id(texture_id), m_scale(scale), m_tile_size(tile_size),  m_entity_manager(entity_manager)
	{
	}

	void TileMap::LoadMap(const char* filename, int map_size_x, int map_size_y)
	{
		std::ifstream input_stream(filename);
		if (input_stream.good())
		{
			for (int y = 0; y < map_size_y; ++y)
			{
				for (int x = 0; x < map_size_x; ++x)
				{
					char x_pos, y_pos;
					input_stream.get(y_pos);
					input_stream.get(x_pos);
					input_stream.ignore();

					int src_x = std::atoi(&x_pos) * m_tile_size;
					int src_y = std::atoi(&y_pos) * m_tile_size;

					AddTile(src_x, src_y, x * m_scale * m_tile_size, y * m_scale * m_tile_size);
					

					std::cout << x_pos << y_pos << ",";
				}
				std::cout << std::endl;

			}
		}

		input_stream.close();
	}

	void TileMap::AddTile(int source_x, int source_y, int x, int y)
	{
		auto  entity_name	= "tile_" + std::to_string(x) + "_" + std::to_string(y);
		auto& entity		= m_entity_manager.AddEntity(entity_name.c_str(), EngineConstant::Layer::TILEMAP);

		entity.AddComponent<TileComponent>(m_texture_id.c_str(), source_x, source_y, x, y, m_tile_size, m_scale);
	}

}