#include <iostream>
#include <memory>

#include "Engine.h"
#include "EngineConstant.h"




using namespace T_Engine;

int main(int argc, char** argv)
{
	std::unique_ptr<Engine> engine{ std::make_unique<Engine>() };
	engine->Initialize(EngineConstant::WINDOW_TITLE, EngineConstant::WINDOW_WIDTH, EngineConstant::WINDOW_HEIGHT);

	while (engine->IsRunning())
	{
		engine->ProcessEvent();
		engine->Update();
		engine->Render();
	}


	engine->Destroy();


	return 0;
}