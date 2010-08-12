#include "GameCommonIncludes.h"
#include "GameManager.h"
#include "GameScreen.h"

GameManager::GameManager()
	: mActiveScreen(0)
{
	rt::InputManager::Get()->RegisterBind(sf::Mouse::XButton1, "toggle_fullscreen");

	rt::ConsoleManager::Get()->RegisterExec("change_screen", &GameManager::ChangeScreen, this);

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