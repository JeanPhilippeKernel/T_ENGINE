#pragma once

#include <glm/glm.hpp>
#include "../IComponent.h"

namespace T_Engine
{
	namespace Component
	{
		class TransformComponent : public IComponent
		{
		public:
			explicit TransformComponent(float pos_x, float  pos_y, float  vel_x, float  vel_y, int width, int height, float scale_xy);
			explicit TransformComponent(float pos_x, float  pos_y, float  vel_x, float  vel_y, int width, int height, float scale_x, float scale_y);
			explicit TransformComponent(glm::vec2 position, glm::vec2 velocity, glm::vec2 size, glm::vec2 scale);
			virtual ~TransformComponent()	= default;


			int height()	const { return m_height; }
			int width()		const { return m_width; }

			void width(int value)	{ m_width	= value; }
			void height(int value)	{ m_height	= value; }

			const glm::vec2& position()		const { return m_position; }
			const glm::vec2& velocity()		const { return m_velocity; }
			const glm::vec2& scale()		const { return m_scale; }

			void position(glm::vec2 value)	{ m_position	= value; }
			void velocity(glm::vec2 value)	{ m_velocity	= value; }
			void scale(glm::vec2 value)		{ m_scale		= value; }


			void Initialize()				override;
			void Update(float delta_time)	override;
			void Render()					override;



		private:
			int m_height	{ 0 };
			int m_width		{ 0 };

			glm::vec2 m_position;
			glm::vec2 m_velocity;
			glm::vec2 m_scale;
		};

	}
}
