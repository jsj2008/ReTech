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
#include "rtGuiManager.h"
#include "rtGuiScreen.h"
#include "ReTechLogManager.h"

URegisterSingleton(GuiManager)

namespace rt
{
	GuiManager::GuiManager()
	{
		mGui.reset(new sfg::GUI(sf::FloatRect(0.0f, 0.0f, 
			static_cast<float>(OptionsManager::Get()->GetOption("width").ToInt()), 
			static_cast<float>(OptionsManager::Get()->GetOption("height").ToInt()))));

		mGui->LoadSkinFromFile( OptionsManager::Get()->GetOption("media_dir").ToString() + OptionsManager::Get()->GetOption("gui_skin").ToString() );
	}

	GuiManager::~GuiManager()
	{
	}

	void GuiManager::Update( float iFrameTime )
	{
	}

	bool GuiManager::HandleEvent( const sf::Event& iEvent )
	{
		return mGui->HandleEvent(iEvent);
	}

	void GuiManager::Render()
	{
		mGui->Render(*GameCore::Get()->GetMainWindow());
	}

	sfg::GUI* GuiManager::GetGui()
	{
		return mGui.get();
	}

	void GuiManager::AddScreen( const std::string& iName, GuiScreen* iScreen )
	{
		if(mScreens.find(iName) != mScreens.end())
		{
			//TODO log
			return;
		}

		mScreens[iName].reset(iScreen);
	}

	void GuiManager::ChangeScreen( const std::string& iName )
	{
		ClearScreens();

		if(mScreens.find(iName) == mScreens.end())
		{
			//TODO log
			return;
		}

		mScreenStack.push_back(mScreens[iName].get());
		mScreenStack.back()->Activated();
	}

	void GuiManager::PushScreen( const std::string& iName )
	{
		if(mScreens.find(iName) == mScreens.end())
		{
			//TODO log
			return;
		}

		if(!mScreenStack.empty())
		{
			mScreenStack.back()->Paused();
		}

		mScreenStack.push_back(mScreens[iName].get());
		mScreenStack.back()->Activated();
	}

	void GuiManager::PopScreen()
	{
		if(!mScreenStack.empty())
		{
			mScreenStack.back()->Deactivated();
		}

		if(!mScreenStack.empty())
		{
			mScreenStack.back()->Resumed();
		}
	}

	void GuiManager::ClearScreens()
	{
		for(ScreenVecIter iter = mScreenStack.begin(); iter != mScreenStack.end(); ++iter)
		{
			(*iter)->Deactivated();
		}

		mScreenStack.clear();
	}
}
