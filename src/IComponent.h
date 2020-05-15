#pragma once
#include <memory>
#include "Entity.h"


namespace T_Engine
{
	class Entity;

	struct IComponent
	{
		IComponent()								= default;
		virtual ~IComponent()						= default;

		virtual void Initialize()					= 0;
		virtual void Update(float delta_time)		= 0;
		virtual void Render()						= 0;


		const Entity* Owner_ptr						{ nullptr };
	};
}
