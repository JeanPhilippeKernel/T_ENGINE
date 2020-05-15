#pragma once

#include <cstdint>

namespace T_Engine
{
	class EngineConstant
	{
	public:
		EngineConstant() = delete;
	
	public:
		static constexpr const char*		WINDOW_TITLE				{ "T_ENGINE" };
		static constexpr std::uint32_t		WINDOW_WIDTH				{ 800 };
		static constexpr std::uint32_t		WINDOW_HEIGHT				{ 600 };
		
		
		static constexpr std::uint32_t		FPS							{ 60 };
		static constexpr float				TIME_TARGET_PER_FRAME		{ 1000.0f / FPS };

		class Animation;
		static constexpr std::uint32_t		ANIMATION_COUNT				{ 5 };


		enum class Layer;
		static constexpr std::uint32_t		LAYER_COUNT					{ 6 };

	};


	class EngineConstant::Animation
	{
	public:
		Animation() = delete;

		static constexpr const char*		UP_ANIMATION				{ "up_animation" };
		static constexpr const char*		RIGHT_ANIMATION				{ "right_animation" };
		static constexpr const char*		DOWN_ANIMATION				{ "down_animation" };
		static constexpr const char*		LEFT_ANIMATION				{ "left_animation" };
		static constexpr const char*		SINGLE_ANIMATION			{ "single_animation" };

	};

	enum class EngineConstant::Layer
	{
		TILEMAP,
		VEGETATION,
		ENEMY,
		PLAYER,
		PROJECTILE,
		UI
	};
}