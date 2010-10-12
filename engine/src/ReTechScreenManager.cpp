/*
Copyright (c) 2010 Alexander Novitsky                                             

Permission is hereby granted, free of charge, to any person obtaining a copy  
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights  
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     
copies of the Software, and to permit persons to whom the Software is         
furnished to do so, subject to the following conditions:                      

The above copyright notice and this permission notice shall be included in    
all copies or substantial portions of the Software.                           

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     
THE SOFTWARE.
*/

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

		mScreens[iScreenName].reset(iScreen);
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

		mScreenStack.push_back(mScreens[iScreenName].get());

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
