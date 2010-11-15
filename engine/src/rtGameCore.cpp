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

#include "rtCommonIncludes.h"
#include "rtGameCore.h"

#include "rtSerializeable.h"

#include "rtImage.h"
#include "rtFont.h"
#include "rtSequence.h"
#include "rtParticle.h"
#include "rtSound.h"
#include "rtMusic.h"

#include "rtComponent.h"
#include "rtSprite.h"
#include "rtAnimation.h"
#include "rtText.h"
#include "rtParticleSystem.h"
#include "rtLine.h"
#include "rtCircle.h"
#include "rtRectangle.h"

#include "rtWorldObject.h"
#include "rtActorObject.h"
#include "rtStaticObject.h"

URegisterSingleton(GameCore)

rt::RTID rt::GameCore::mLastId = 0;

namespace rt
{
	GameCore::GameCore()
		: mIsFullscreen(false), mRandomizeSeed(0)
	{
		mExec		= ConsoleManager::Ptr(new ConsoleManager());
		mOptions	= OptionsManager::Ptr(new OptionsManager()); 
		mLog		= LogManager::Ptr(new LogManager());
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

		mRandomizeSeed = (int)time(0);

		//Create managers
		mRender		= RenderManager::Ptr(new RenderManager());
		mInput		= InputManager::Ptr(new InputManager());
		mResource	= ResourceManager::Ptr(new ResourceManager());
		mWorlds		= WorldsManager::Ptr(new WorldsManager());
		mGui		= GuiManager::Ptr(new GuiManager());
		mTools		= ToolManager::Ptr(new ToolManager());
		mPhysics	= PhysicsManager::Ptr(new PhysicsManager());
		mAudio		= AudioManager::Ptr(new AudioManager());

		//Register classes
		URegisterObject(Serializeable);

		URegisterObject(Font);
		URegisterObject(Image);
		URegisterObject(Particle);
		URegisterObject(Sequence);
		URegisterObject(Sound);
		URegisterObject(Music);

		URegisterObject(Component);
		URegisterObject(Animation);
		URegisterObject(Circle);
		URegisterObject(Line);
		URegisterObject(ParticleSystem);
		URegisterObject(Rectangle);
		URegisterObject(Sprite);
		URegisterObject(Text);

		URegisterObject(WorldObject);
		URegisterObject(ActorObject);
		URegisterObject(StaticObject);

		//Register resource classes
		mResource->RegisterExtension(".tga", "Image");
		mResource->RegisterExtension(".png", "Image");
		mResource->RegisterExtension(".ttf", "Font");
		mResource->RegisterExtension(".seq", "Sequence");
		mResource->RegisterExtension(".ps", "Particle");
		mResource->RegisterExtension(".ogg", "Music");

		mResource->CreateResources();

		//Register execs
		mExec->RegisterCommand("quit", this, "Stop");
		mExec->RegisterCommand("set_fullscreen", this, "SetFullscreen");
		mExec->RegisterCommand("toggle_fullscreen", this, "ToggleFullscreen");

		ULogNotice("GameCore initialized.");
	}

	void GameCore::Run()
	{
		sf::Randomizer::SetSeed(mRandomizeSeed);

		while (mMainWindow->IsOpened())
		{
			float frameTime = mMainWindow->GetFrameTime();

			mInput->Update(frameTime);
			mGui->Update(frameTime);
			mWorlds->Update(frameTime);
			mTools->Update(frameTime);
			mRender->Update(frameTime);
			mPhysics->Update(frameTime);
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

		mMainWindow->ShowMouseCursor(false);
		mMainwindow->SetFocus();
	}
}