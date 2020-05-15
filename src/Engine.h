#pragma once

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include <memory>

#include "EntityManager.h"
#include "AssetManager.h"
#include "TileMap.h"
#include "CollisionManager.h"


namespace T_Engine
{
	class AssetManager;
	class EntityManager;
	class CollisionManager;

	class Engine 
	{
	public:
		Engine()	= default;
		~Engine();

		void Initialize(const char * window_title, std::uint32_t width, std::uint32_t height);
		void Destroy();

		bool IsRunning() const;



		void LoadScene(int scene_index = 0);

		void ProcessEvent();
		void Update();
		void Render();

	public: 
		static SDL_Renderer*						Renderer;

		static std::unique_ptr<AssetManager>		AssetManager;
		static std::unique_ptr<EntityManager>		EntityManager;
		static std::unique_ptr<CollisionManager>	CollisionManager;
		static std::unique_ptr<SDL_Event>			Event;

		static std::shared_ptr<SDL_Rect>			Camera;

	private:
		bool									m_is_running		{ false };
		SDL_Window*								m_window			{ nullptr };

		std::uint32_t							m_last_time_tick	{ 0 };
		std::unique_ptr<TileMap>				m_tile_map			{ nullptr };
	};
}

