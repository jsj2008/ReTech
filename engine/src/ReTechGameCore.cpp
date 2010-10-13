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
#include "ReTechGameCore.h"

#include "ReTechImage.h"
#include "ReTechFont.h"
#include "ReTechSequence.h"
#include "ReTechParticle.h"

#include "ReTechSprite.h"
#include "ReTechAnimation.h"
#include "ReTechButton.h"
#include "ReTechText.h"
#include "ReTechParticleSystem.h"
#include "ReTechLine.h"
#include "ReTechCircle.h"
#include "ReTechRectangle.h"

URegisterSingleton(GameCore)

rt::RTID rt::GameCore::mLastId = 0;

namespace rt
{
	GameCore::GameCore()
		: mIsFullscreen(false), mRandomizeSeed(0)
	{

	}

	GameCore::~GameCore()
	{

	}

	void GameCore::Initialize()
	{
		int width = OptionsManager::Get()->GetOption("width").ToInt();
		int height = OptionsManager::Get()->GetOption("height").ToInt();

		mMainView.reset(new sf::View(sf::Vector2f(width * 0.5f, height * 0.5f), 
			sf::Vector2f(static_cast<float>(width), static_cast<float>(height))));

		recreateWindow();

		mMainWindow->ShowMouseCursor(false);

		mRandomizeSeed = (int)time(0);

		mLog.Initialize();

		//Register objects to factory
		URegisterObject(Image);
		URegisterObject(Font);
		URegisterObject(Sequence);
		URegisterObject(Particle);
		URegisterObject(Sprite);
		URegisterObject(Animation);
		URegisterObject(Button);
		URegisterObject(Text);
		URegisterObject(ParticleSystem);
		URegisterObject(Line);
		URegisterObject(Circle);
		URegisterObject(Rectangle);

		//Register resource classes
		mResource.RegisterExtension("tga", "Image");
		mResource.RegisterExtension("png", "Image");
		mResource.RegisterExtension("ttf", "Font");
		mResource.RegisterExtension("seq", "Sequence");
		mResource.RegisterExtension("ps", "Particle");

		mResource.CreateResources();
		mGui.CreateGui();

		//Register execs
		mExec.RegisterExec("quit", &GameCore::Stop, this);
		mExec.RegisterExec("set_fullscreen", &GameCore::SetFullscreen, this);
		mExec.RegisterExec("toggle_fullscreen", &GameCore::ToggleFullscreen, this);

		LogManager::Get()->Notice("GameCore initialized.");
	}

	void GameCore::Run()
	{
		sf::Randomizer::SetSeed(mRandomizeSeed);

		while (mMainWindow->IsOpened())
		{
			float frameTime = mMainWindow->GetFrameTime();

			mInput.Update(frameTime);
			mGui.Update(frameTime);
			mWorlds.Update(frameTime);
			mRender.Update(frameTime);
		}
	}

	void GameCore::Stop()
	{
		mMainWindow->Close();
	}

	void GameCore::Shutdown()
	{
	}

	RTID GameCore::CreateUniqueId()
	{
		return mLastId++;
	}

	sf::RenderWindow* GameCore::GetMainWindow()
	{
		return mMainWindow.get();
	}

	sf::View* GameCore::GetMainView()
	{
		return mMainView.get();
	}

	void GameCore::SetFullscreen( bool iIsFullscreen )
	{
		if(mIsFullscreen != iIsFullscreen)
		{
			mIsFullscreen = iIsFullscreen;

			recreateWindow();
		}		
	}

	void GameCore::ToggleFullscreen()
	{
		mIsFullscreen = !mIsFullscreen;

		recreateWindow();
	}

	void GameCore::recreateWindow()
	{
		int width = OptionsManager::Get()->GetOption("width").ToInt();
		int height = OptionsManager::Get()->GetOption("height").ToInt();

		mMainWindow.reset(new sf::RenderWindow(sf::VideoMode(width, height, OptionsManager::Get()->GetOption("bpp").ToInt()), 
			OptionsManager::Get()->GetOption("title").ToString(), mIsFullscreen ? sf::Style::Fullscreen : sf::Style::Close));

		if(!mIsFullscreen)
		{
			mMainWindow->SetSize(width, height);
		}

		mMainWindow->SetView(*mMainView);
	}
}