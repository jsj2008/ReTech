#include "GameCommonIncludes.h"
#include "GameManager.h"
#include "GameScreen.h"

GameManager::GameManager()
{
	rt::InputManager::Get()->RegisterBind(sf::Mouse::XButton1, "toggle_fullscreen");

	rt::ConsoleManager::Get()->RegisterExec("change_screen", &GameManager::ChangeScreen, this);

	mScreens["main_menu"].assign(new GameScreen(this, "./data/worlds/main_menu_screen.world"));
	mScreens["lobby_dwarfs"].assign(new GameScreen(this, "./data/worlds/lobby_dwarfs_screen.world"));

	ChangeScreen("main_menu");
}

GameManager::~GameManager()
{
	ClearScreens();
}

void GameManager::Update( float iFrameTime )
{
	if(!mScreenStack.empty())
	{
		mScreenStack.back()->Update(iFrameTime);
	}
}

void GameManager::PushScreen( const std::string& iScreenName )
{
	if(!mScreenStack.empty())
	{
		mScreenStack.back()->Paused();
	}

	mScreenStack.push_back(mScreens[iScreenName]);

	mScreenStack.back()->Pushed();
}

void GameManager::PopScreen()
{
	if(!mScreenStack.empty())
	{
		mScreenStack.back()->Poped();
		mScreenStack.pop_back();
	}

	if(!mScreenStack.empty())
	{
		mScreenStack.back()->Resumed();
	}
}

void GameManager::ChangeScreen( const std::string& iScreenName )
{
	ClearScreens();
	PushScreen(iScreenName);
}

void GameManager::ClearScreens()
{
	for(ScreenStack::iterator iter = mScreenStack.begin(); iter != mScreenStack.end(); ++iter)
	{
		(*iter)->Poped();
	}

	mScreenStack.clear();
}