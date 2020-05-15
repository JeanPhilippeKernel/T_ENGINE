#pragma once

#include <map>
#include <vector>
#include <memory>
#include "Entity.h"
#include "EngineConstant.h"

namespace T_Engine
{
	class Entity;

	class EntityManager
	{
	public:
		EntityManager()		= default;
		~EntityManager()	= default;

		Entity&													AddEntity(const char* entity_name, EngineConstant::Layer layer);
		bool													RemoveEntity(const char* entity_name, EngineConstant::Layer layer);
		bool													HasNoEntities()		const;
		size_t													GetCount()			const;
		std::vector<T_Engine::Entity*>							GetEntities()		const =  delete;
		std::vector<T_Engine::Entity*>							GetEntityByLayer(size_t count, EngineConstant::Layer layers...)	const;


		void Update(float delta_time);
		void Render();

	private:
		std::map<EngineConstant::Layer, std::vector<std::unique_ptr<Entity>>> m_entity_collection;
	};

}