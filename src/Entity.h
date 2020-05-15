#pragma once

#include <type_traits>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <vector>
#include <map>
#include <iostream>
#include <SDL2/SDL.h>
#include <functional>

#include "IComponent.h"
#include "EntityManager.h"
#include "EngineConstant.h"
#include "CollisionManager.h"

namespace T_Engine
{
	class EntityManager;
	struct IComponent;

	class Entity
	{
	public:
		Entity() = default;
		Entity(const EntityManager& entity_manager, const char* name, EngineConstant::Layer layer)
			:m_entity_manager(entity_manager), m_name(name), m_layer(layer)
		{
			m_attached_camera = std::make_shared<SDL_Rect>();
		}

		~Entity() = default;
		
		const std::string&			name()					const	{ return m_name; }
		const EntityManager&		entity_manager()		const	{ return m_entity_manager; }
		const EngineConstant::Layer layer()					const	{ return m_layer; }
		bool						has_camera_attached()	const	{ return m_has_camera_attached; }

		template
		<
			typename T,
			typename... TArgs,
			typename = std::enable_if_t<std::is_base_of_v<IComponent, T>> 
		>
		void AddComponent(TArgs&&... args)
		{
			auto it = std::find_if(
				std::begin(m_component_type_map), std::end(m_component_type_map),
				[](const std::pair<const type_info * const, IComponent *>& key_val) 
				{ 
					return  strcmp(key_val.first->name(), typeid(T).name()) == 0;
				}
			);
			
			if (it != std::end(m_component_type_map))
			{
				std::cerr << "this entity already have this component" << std::endl;
				exit(EXIT_FAILURE);
			}

			std::unique_ptr<IComponent> component = std::make_unique<T>((args)...);
			
			component->Owner_ptr = this;
			component->Initialize();
			
			auto& back = m_components.emplace_back(std::move(component));
			m_component_type_map.emplace(&typeid(*back.get()), back.get());
		}
	

		template
		<
			typename T,
			typename = std::enable_if_t<std::is_base_of_v<IComponent, T>>
		>
		bool HasComponent()	const
		{
			bool result{ false };
			auto it = std::find_if(
				std::begin(m_component_type_map), std::end(m_component_type_map),
				[](const std::pair<const type_info* const, IComponent*>& key_val)
				{
					return  strcmp(key_val.first->name(), typeid(T).name()) == 0;
				}
			);

			if (it != std::end(m_component_type_map))
				result = true;
			
			return result;
		}
		

		template
		<
			typename T,
			typename = std::enable_if_t<std::is_base_of_v<IComponent, T>>
		>
			const T* GetComponent() const
		{
			auto it = std::find_if(
				std::begin(m_component_type_map), std::end(m_component_type_map),
				[](const std::pair<const type_info* const, IComponent*>& key_val)
				{
					return  strcmp(key_val.first->name(), typeid(T).name()) == 0;
				}
			);

			if (it != std::end(m_component_type_map))
				return dynamic_cast<T*>(it->second);
			
			return nullptr;
		}


		template<typename T, typename = std::enable_if_t<std::is_base_of_v<IComponent, T>>>
		bool RemoveComponent() = delete;


		void AttachCamera(const std::shared_ptr<SDL_Rect>& camera);

		void Update(float delta_time);
		void Render();

		

	public:
		void OnRender(std::function<void(void)> callback)								{ m_render_callback = callback; }
		void OnUpdate(std::function<void(float)> callback)								{ m_update_callback = callback; }
		
		void OnCollision(std::function<void(const Entity&, const Entity&)> callback)	{ m_collision_callback = callback; }


	private:
		std::string											m_name{};
		const EntityManager&								m_entity_manager;
		EngineConstant::Layer								m_layer;

		std::vector<std::unique_ptr<IComponent>>			m_components;
		std::map<const type_info* const, IComponent*>		m_component_type_map;

		std::shared_ptr<SDL_Rect>							m_attached_camera;
		bool												m_has_camera_attached{ false };


		std::function<void(const Entity&, const Entity&)>	m_collision_callback;
		std::function<void(float)>							m_update_callback;
		std::function<void(void)>							m_render_callback;

		void _VerifyCollision() const;

	};
}
