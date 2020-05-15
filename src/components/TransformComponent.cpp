#pragma once
#include "TransformComponent.h"
#include <SDL2/SDL.h>
#include "../Engine.h"

namespace T_Engine
{
	namespace Component
	{

		TransformComponent::TransformComponent(float pos_x, float  pos_y, float  vel_x, float  vel_y, int width, int height, float scale_xy)
		{
			m_position	= glm::vec2( pos_x, pos_y );
			m_velocity	= glm::vec2( vel_x, vel_y );
			m_scale		= glm::vec2( scale_xy, scale_xy );
			m_width		= width;
			m_height	= height;
		}

		TransformComponent::TransformComponent(float pos_x, float  pos_y, float  vel_x, float  vel_y, int width, int height, float scale_x, float scale_y)
		{
			m_position	= glm::vec2(pos_x, pos_y);
			m_velocity	= glm::vec2(vel_x, vel_y);
			m_scale		= glm::vec2(scale_x, scale_y);
			m_width		= width;
			m_height	= height;
		}

		TransformComponent::TransformComponent(glm::vec2 position, glm::vec2 velocity, glm::vec2 size, glm::vec2 scale)
			:m_position(position), m_velocity(velocity), m_scale(scale), m_width(size.x), m_height(size.y)
		{
		}


		void TransformComponent::Initialize() {}

		void TransformComponent::Update(float delta_time)
		{
			m_position.x += m_velocity.x * delta_time;
			m_position.y += m_velocity.y * delta_time;
		}

		void TransformComponent::Render() {}

	}
}