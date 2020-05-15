#include <algorithm>
#include <exception>
#include "EntityManager.h"

namespace T_Engine
{
	Entity& EntityManager::AddEntity(const char* entity_name, EngineConstant::Layer layer)
	{
		auto& collection = m_entity_collection[layer];

		auto it = std::find_if(
			std::begin(collection), std::end(collection),
			[&entity_name](const auto& entity_ptr) { return strcmp(entity_ptr->name().c_str(), entity_name) == 0; }
		);

		if (it == collection.end())
		{
			auto entity{ std::make_unique<Entity>(*this, entity_name, layer) };
			collection.emplace_back(std::move(entity));
			return *(collection.back());
		}
		else
			throw std::exception("entity name must be unique");
	}

	bool EntityManager::RemoveEntity(const char* entity_name, EngineConstant::Layer layer)
	{
		bool result{ false };

		auto& collection = m_entity_collection[layer];

		auto it = std::find_if(
			std::begin(collection), std::end(collection),
			[&entity_name](const auto& entity_ptr) { return strcmp(entity_ptr->name().c_str(), entity_name) == 0; }
		);

		if (it != std::end(collection))
		{
			collection.erase(it);
			result = true;
		}

		return result;
	}

	bool EntityManager::HasNoEntities()	const
	{
		return m_entity_collection.empty();
	}

	size_t EntityManager::GetCount() const
	{
		return m_entity_collection.size();
	}

	std::vector<T_Engine::Entity*> EntityManager::GetEntityByLayer(size_t count, EngineConstant::Layer layers...) const
	{
		std::vector<T_Engine::Entity*> result{};

		va_list args;
		va_start(args, count);
		for (int x = 0; x < count; ++x)
		{
			EngineConstant::Layer layer = va_arg(args, EngineConstant::Layer);
			auto it = std::find_if(
				std::begin(m_entity_collection), std::end(m_entity_collection),
				[&](const auto& p) { return p.first == layer; }
			);
			if (it != std::end(m_entity_collection)) {
				for (const auto& item : it->second)
					result.push_back(item.get());
			}
		}
		
		va_end(args);

		return result;
	}



	//std::vector<T_Engine::Entity*> EntityManager::GetEntities()  const 
	//{
	//	std::vector<T_Engine::Entity*> result{};

	//	//for (const auto& item : m_entity_collection.at(EngineConstant::Layer::TILEMAP))
	//		//result.push_back(item.get());


	//	/*for (const auto& item : m_entity_collection.at(EngineConstant::Layer::VEGETATION))
	//		result.push_back(item.get());*/


	//	//for (const auto& item : m_entity_collection.at(EngineConstant::Layer::ENEMY))
	//	//	result.push_back(item.get());


	//	//for (const auto& item : m_entity_collection.at(EngineConstant::Layer::PROJECTILE))
	//	//	result.push_back(item.get());


	//	for (const auto& item : m_entity_collection.at(EngineConstant::Layer::PLAYER))
	//		result.push_back(item.get());


	//	//for (const auto& item : m_entity_collection.at(EngineConstant::Layer::UI))
	//		//result.push_back(item.get());

	//	return result;
	//}								 


	void EntityManager::Update(float delta_time)
	{
	
		for (const auto& item : m_entity_collection[EngineConstant::Layer::TILEMAP])
			item->Update(delta_time);


		for (const auto& item : m_entity_collection[EngineConstant::Layer::VEGETATION])
			item->Update(delta_time);


		for (const auto& item : m_entity_collection[EngineConstant::Layer::ENEMY])
			item->Update(delta_time);


		for (const auto& item : m_entity_collection[EngineConstant::Layer::PROJECTILE])
			item->Update(delta_time);


		for (const auto& item : m_entity_collection[EngineConstant::Layer::PLAYER])
			item->Update(delta_time);


		for (const auto& item : m_entity_collection[EngineConstant::Layer::UI])
			item->Update(delta_time);
	}
	
	void EntityManager::Render()
	{
		for (const auto& item : m_entity_collection[EngineConstant::Layer::TILEMAP])
			item->Render();


		for (const auto& item : m_entity_collection[EngineConstant::Layer::VEGETATION])
			item->Render();


		for (const auto& item : m_entity_collection[EngineConstant::Layer::ENEMY])
			item->Render();


		for (const auto& item : m_entity_collection[EngineConstant::Layer::PROJECTILE])
			item->Render();


		for (const auto& item : m_entity_collection[EngineConstant::Layer::PLAYER])
			item->Render();


		for (const auto& item : m_entity_collection[EngineConstant::Layer::UI])
			item->Render();
	}

}