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

rt::World* GameScreen::GetWorld()
{
	return mWorld;
}