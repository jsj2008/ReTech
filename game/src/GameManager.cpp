#include "GameCommonIncludes.h"
#include "GameManager.h"
#include "GameScreen.h"
#include "MainMenuScreen.h"
#include "LobbySurvivorsScreen.h"
#include "LobbyArsenalScreen.h"
#include "LobbyJobScreen.h"
#include "LobbyTacticsScreen.h"
#include "LobbyWorldScreen.h"

GameManager::GameManager()
	: mActiveScreen(0)
{
	rt::InputManager::Get()->RegisterBind(sf::Key::Escape, "quit");

	rt::ConsoleManager::Get()->RegisterExec("change_screen", &GameManager::ChangeScreen, this);

	rt::ConsoleManager::Get()->RegisterExec("activate_main_menu", &GameManager::ActivateMainMenu, this);
	rt::ConsoleManager::Get()->RegisterExec("activate_lobby_survivors", &GameManager::ActivateLobbySurvivors, this);
	rt::ConsoleManager::Get()->RegisterExec("activate_lobby_arsenal", &GameManager::ActivateLobbyArsenal, this);
	rt::ConsoleManager::Get()->RegisterExec("activate_lobby_job", &GameManager::ActivateLobbyJob, this);
	rt::ConsoleManager::Get()->RegisterExec("activate_lobby_tactics", &GameManager::ActivateLobbyTactics, this);
	rt::ConsoleManager::Get()->RegisterExec("activate_lobby_world", &GameManager::ActivateLobbyWorld, this);

	mScreens["main_menu"].assign(new MainMenuScreen(this));
	mScreens["lobby_survivors"].assign(new LobbySurvivorsScreen(this));
	mScreens["lobby_arsenal"].assign(new LobbyArsenalScreen(this));
	mScreens["lobby_job"].assign(new LobbyJobScreen(this));
	mScreens["lobby_tactics"].assign(new LobbyTacticsScreen(this));
	mScreens["lobby_world"].assign(new LobbyWorldScreen(this));

	ActivateMainMenu();
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

void GameManager::ActivateMainMenu()
{
	ChangeScreen("main_menu");
}

void GameManager::ActivateLobbySurvivors()
{
	ChangeScreen("lobby_survivors");
}

void GameManager::ActivateLobbyArsenal()
{
	ChangeScreen("lobby_arsenal");
}

void GameManager::ActivateLobbyJob()
{
	ChangeScreen("lobby_job");
}

void GameManager::ActivateLobbyTactics()
{
	ChangeScreen("lobby_tactics");
}

void GameManager::ActivateLobbyWorld()
{
	ChangeScreen("lobby_world");
}

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