#include "ReTechCommonIncludes.h"
#include "ReTechScreenManager.h"
#include "ReTechScreen.h"
#include "ReTechLogManager.h"

URegisterSingleton(ScreenManager)

namespace rt
{
	ScreenManager::ScreenManager()
	{
		rt::ConsoleManager::Get()->RegisterExec("change_screen", &ScreenManager::ChangeScreen, this);
	}

	ScreenManager::~ScreenManager()
	{
		ClearScreens();
	}

	void ScreenManager::AddScreen( const std::string& iScreenName, Screen* iScreen )
	{
		if(mScreens.find(iScreenName) != mScreens.end())
		{
			LogManager::Get()->Warning(iScreenName + " already exists");
		}

		mScreens[iScreenName].assign(iScreen);
	}

	void ScreenManager::Update( float iFrameTime )
	{
		if(!mScreenStack.empty())
		{
			mScreenStack.back()->Update(iFrameTime);
		}
	}

	void ScreenManager::PushScreen( const std::string& iScreenName )
	{
		if(!mScreenStack.empty())
		{
			mScreenStack.back()->Paused();
		}

		mScreenStack.push_back(mScreens[iScreenName]);

		mScreenStack.back()->Pushed();
	}

	void ScreenManager::PopScreen()
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

	void ScreenManager::ChangeScreen( const std::string& iScreenName )
	{
		ClearScreens();
		PushScreen(iScreenName);
	}

	void ScreenManager::ClearScreens()
	{
		for(ScreenStack::iterator iter = mScreenStack.begin(); iter != mScreenStack.end(); ++iter)
		{
			(*iter)->Poped();
		}

		mScreenStack.clear();
	}
}
