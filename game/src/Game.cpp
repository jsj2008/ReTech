#include "GameCommonIncludes.h"
#include "GameLibraries.h"

#include "GameManager.h"

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
	rt::GameCore gameCore;

	rt::OptionsManager::Get()->GetOption("title") = std::string("ReTech Engine v 0.2.0");
	rt::OptionsManager::Get()->GetOption("width") = 1280;
	rt::OptionsManager::Get()->GetOption("height") = 720;
	rt::OptionsManager::Get()->GetOption("bpp") = 32;
	rt::OptionsManager::Get()->GetOption("media_dir") = std::string("./media/");

	gameCore.Initialize();

	rt::World* mainWorld = rt::WorldsManager::Get()->CreateWorld("main");
	mainWorld->AddObject(new GameManager());

	gameCore.Run();

	gameCore.Shutdown();

	return EXIT_SUCCESS;
}