#include "GameCommonIncludes.h"
#include "GameScreen.h"
#include "GameManager.h"

GameScreen::GameScreen(GameManager* iManager, const std::string& iLevelName)
	: mManager(iManager)
{
	mWorld = rt::WorldsManager::Get()->CreateWorld(iLevelName);

	if(!iLevelName.empty())
	{
		mWorld->Load(iLevelName, false);
	}
}

GameScreen::~GameScreen()
{
	rt::WorldsManager::Get()->DestroyWorld(mWorld->GetName());
}

void GameScreen::Pushed()
{
	if(mWorld->IsLoaded())
	{
		mWorld->SetVisible(true);
	}
}

void GameScreen::Poped()
{
	if(mWorld->IsLoaded())
	{
		mWorld->SetVisible(false);
	}
}

void GameScreen::Paused()
{

}

void GameScreen::Resumed()
{

}

void GameScreen::Update( float iFrameTime )
{
	if(!mWorld->IsVisible() && mWorld->IsLoaded())
	{
		mWorld->SetVisible(true);
	}
}

rt::World* GameScreen::GetWorld()
{
	return mWorld;
}