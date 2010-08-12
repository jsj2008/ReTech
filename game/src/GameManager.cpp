#include "GameCommonIncludes.h"
#include "GameManager.h"
#include "GameScreen.h"
#include "MainMenuScreen.h"
#include "LobbyDwarfsScreen.h"

GameManager::GameManager()
	: mActiveScreen(0)
{
	rt::InputManager::Get()->RegisterBind(sf::Mouse::XButton1, "toggle_fullscreen");

	rt::ConsoleManager::Get()->RegisterExec("change_screen", &GameManager::ChangeScreen, this);

	//fastdelegate::FastDelegate1<const std::string&> test1 = rt::ConsoleManager::Get()->GetExec("change_screen");
	//fastdelegate::FastDelegate1<const std::string&> test = fastdelegate::MakeDelegate(this, &GameManager::ChangeScreen);
	//test(std::string("test"));
	//test1(std::string("test"));

	//rt::ConsoleManager::Get()->RegisterExec("activate_main_menu", &GameManager::ActivateMainMenu, this);
	//rt::ConsoleManager::Get()->RegisterExec("activate_lobby_dwarfs", &GameManager::ActivateLobbyDwarfs, this);

	mScreens["main_menu"].assign(new GameScreen(this, "./data/worlds/main_menu_screen.world"));
	mScreens["lobby_dwarfs"].assign(new GameScreen(this, "./data/worlds/lobby_dwarfs_screen.world"));

	ChangeScreen("main_menu");
}

GameManager::~GameManager()
{

}

void GameManager::Update( float iFrameTime )
{
	if(!mActiveScreen->GetWorld()->IsVisible() && mActiveScreen->GetWorld()->IsLoaded())
	{
		mActiveScreen->GetWorld()->SetVisible(true);
	}
}

// void GameManager::ActivateMainMenu()
// {
// 	ChangeScreen("main_menu");
// }
// 
// void GameManager::ActivateLobbyDwarfs()
// {
// 	ChangeScreen("lobby_dwarfs");
// }

void GameManager::ChangeScreen( const std::string& iScreenName )
{
	if(mActiveScreen && mActiveScreen->GetWorld()->IsLoaded())
	{
		mActiveScreen->GetWorld()->SetVisible(false);
	}

	mActiveScreen = mScreens[iScreenName];

	if(mActiveScreen && mActiveScreen->GetWorld()->IsLoaded())
	{
		mActiveScreen->GetWorld()->SetVisible(true);
	}
}