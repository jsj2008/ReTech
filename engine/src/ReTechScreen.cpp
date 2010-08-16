#include "ReTechCommonIncludes.h"
#include "ReTechScreen.h"
#include "ReTechWorld.h"

namespace rt
{
	Screen::Screen(const std::string& iLevelName)
	{
		mWorld = WorldsManager::Get()->CreateWorld(iLevelName);

		if(!iLevelName.empty())
		{
			mWorld->Load(iLevelName, false);
		}
	}

	Screen::~Screen()
	{
		WorldsManager::Get()->DestroyWorld(mWorld->GetName());
	}

	void Screen::Pushed()
	{
		if(mWorld->IsLoaded())
		{
			mWorld->SetVisible(true);
		}
	}

	void Screen::Poped()
	{
		if(mWorld->IsLoaded())
		{
			mWorld->SetVisible(false);
		}
	}

	void Screen::Paused()
	{

	}

	void Screen::Resumed()
	{

	}

	void Screen::Update( float iFrameTime )
	{
		if(!mWorld->IsVisible() && mWorld->IsLoaded())
		{
			mWorld->SetVisible(true);
		}
	}

	rt::World* Screen::GetWorld()
	{
		return mWorld;
	}
}