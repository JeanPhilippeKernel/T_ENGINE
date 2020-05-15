#include "Engine.h"	 
#include "EngineConstant.h"
#include <iostream>
#include <cstdint>


#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"
#include "components/ImageComponent.h"
#include "components/KeyboardComponent.h"
#include "components/ColliderComponent.h"
#include "components/LabelComponent.h"

using namespace T_Engine::Component;



namespace T_Engine
{

	SDL_Renderer*						Engine::Renderer;

	std::unique_ptr<EntityManager>		Engine::EntityManager		= std::make_unique<T_Engine::EntityManager>();
	std::unique_ptr<AssetManager>		Engine::AssetManager		= std::make_unique<T_Engine::AssetManager>(*(Engine::EntityManager.get()));
	std::unique_ptr<CollisionManager>	Engine::CollisionManager	= std::make_unique<T_Engine::CollisionManager>();
	std::unique_ptr<SDL_Event>			Engine::Event				= std::make_unique<SDL_Event>();
	
	std::shared_ptr<SDL_Rect>			Engine::Camera				= std::make_shared<SDL_Rect>();
	


	Engine::~Engine()
	{
		this->m_window	= nullptr;
		Renderer		= nullptr;
		Event			= nullptr;
	}

	void Engine::Initialize(const char* window_title, std::uint32_t width, std::uint32_t height)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cerr << "Error while initializing SDL" << std::endl;
			exit(EXIT_FAILURE);
		}

		if (TTF_Init() != 0) {
			std::cerr << "Error while initializing TTF" << std::endl;
			exit(EXIT_FAILURE);
		}

		int create_operation = SDL_CreateWindowAndRenderer(
			width,
			height,
			SDL_WINDOW_SHOWN,
			&(this->m_window),
			&(this->Renderer)
		);

		if (create_operation != 0) 
		{
			std::cout << "Error while creating window and renderer" << std::endl;
			exit(EXIT_FAILURE);
		}

		SDL_SetWindowTitle(this->m_window, window_title);
		SDL_SetWindowPosition(this->m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
								  
		this->m_is_running = true;

		Camera->x = 0;
		Camera->y = 0;
		Camera->w = EngineConstant::WINDOW_WIDTH;
		Camera->h = EngineConstant::WINDOW_HEIGHT;


		LoadScene();
	}
	
	void Engine::Destroy() 
	{
		SDL_DestroyRenderer(this->Renderer);
		SDL_DestroyWindow(this->m_window);
	}

	bool Engine::IsRunning() const
	{
		return m_is_running;
	}

	void Engine::LoadScene(int scene_index)
	{
		//assets and textures
		AssetManager->AddTexture("tank-texture",		"assets/images/tank-small-left.png");
		AssetManager->AddTexture("chopper-texture",		"assets/images/chopper-spritesheet.png");
		AssetManager->AddTexture("radar-texture",		"assets/images/radar.png");
		AssetManager->AddTexture("tile-map-texture",	"assets/tilemaps/jungle.png");

		AssetManager->AddFont("charriot-font", "assets/fonts/charriot.ttf", 20);

		m_tile_map = std::make_unique<TileMap>(*EntityManager, "tile-map-texture", 2, 32);
		m_tile_map->LoadMap("assets/tilemaps/jungle.map", 25, 20);


		// Entities and their components
		auto& level_label = EntityManager->AddEntity("level-label", EngineConstant::Layer::UI);
		level_label.AddComponent<TransformComponent>(10, 10, 0, 0, 60, 20, 1);
		level_label.AddComponent<LabelComponent>("charriot-font", "level 1", 200, 255, 155);



		auto& tank_entity = EntityManager->AddEntity("tank", EngineConstant::Layer::PLAYER);
		tank_entity.AddComponent<TransformComponent>(10.0f, 20.0f, 30.f, 30.f, 32, 32, 1.f);
		tank_entity.AddComponent<ColliderComponent>(false);
		tank_entity.AddComponent<ImageComponent>("tank-texture");


		auto& chopper_entity = EntityManager->AddEntity("chopper", EngineConstant::Layer::PLAYER);
		chopper_entity.AddComponent<TransformComponent>(200.0f, 300.0f, 30.f, 30.f, 32, 32, 1.f);
		chopper_entity.AddComponent<SpriteComponent>("chopper-texture", 2, 90, true, false);
		chopper_entity.AddComponent<KeyboardComponent>("Up", "Right", "Down", "Left", "Space");
		chopper_entity.AddComponent<ColliderComponent>(false, 250, 100, 150);
		chopper_entity.AttachCamera(Camera);
		chopper_entity.OnCollision([&](const auto& args1, const auto& args2) 
			{
				std::cout << "collision !!" << std::endl;
				this->m_is_running = false;
			}
		);																								 

		auto& radar_entity = EntityManager->AddEntity("radar", EngineConstant::Layer::UI);
		radar_entity.AddComponent<TransformComponent>(900.0f, 20.0f, 30.f, 30.f, 64, 64, 1.f);
		radar_entity.AddComponent<SpriteComponent>("radar-texture", 8, 90, false, true);

	}


	void Engine::ProcessEvent() 
	{
		int has_event = SDL_PollEvent(Event.get());
		if (has_event)
		{
			if (Event->type == SDL_QUIT)
				m_is_running = false;
		
			else if (Event->type == SDL_KEYDOWN)
			{
				if (Event->key.keysym.sym == SDLK_ESCAPE)
					m_is_running = false;
			}
		}
	}
	
	void Engine::Update() 
	{
		std::uint32_t time_to_wait = EngineConstant::TIME_TARGET_PER_FRAME - (SDL_GetTicks() - m_last_time_tick);
		if (time_to_wait > 0 && time_to_wait <= EngineConstant::TIME_TARGET_PER_FRAME)
		{
			SDL_Delay(time_to_wait);
		}

		float  delta_time = (SDL_GetTicks() - m_last_time_tick) / 1000.0f;
		m_last_time_tick = SDL_GetTicks();


		if (!EntityManager->HasNoEntities())
			EntityManager->Update(delta_time);
	}
	
	void Engine::Render() 
	{
		SDL_SetRenderDrawColor(Renderer, 21, 21, 21, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(Renderer);

		if (!EntityManager->HasNoEntities())
			EntityManager->Render();

		SDL_RenderPresent(Renderer);
	}

}