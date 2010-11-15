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

#pragma once

#include "rtSingleton.h"

#include "rtOptionsManager.h"

#include "rtRenderManager.h"
#include "rtInputManager.h"
#include "rtResourceManager.h"
#include "rtLogManager.h"
#include "rtConsoleManager.h"
#include "rtWorldsManager.h"
#include "rtGuiManager.h"
#include "rtToolManager.h"
#include "rtPhysicsManager.h"
#include "rtAudioManager.h"

namespace rt
{
	typedef unsigned int RTID;

	class Atom;

	/**
	*	Main manger class that creates all the stuff and initializes game engine.
	*
	* 	@author Alexander Novitsky
	*/
	class GameCore : public Singleton<GameCore>
	{
	public:
		/**
		* Default constructor
		*
		* @author Alexander Novitsky
		*/
		GameCore();

		/**
		* Default destructor
		*
		* @author Alexander Novitsky
		*/
		~GameCore();

		/**
		* Initializes game engine. Must be called before {@link #Run()}
		*
		* @author Alexander Novitsky
		*/
		void Initialize();


		/**
		* Runs game loop
		*
		* @author Alexander Novitsky
		*/
		void Run();
		void Stop();
		void Shutdown();

		RTID CreateUniqueId();

		sf::RenderWindow*	GetMainWindow();
		sf::View*			GetMainView();

		void SetFullscreen(bool iIsFullscreen);
		void ToggleFullscreen();

		static void RegisterMetaClass()
		{
			camp::Class::declare<GameCore>("GameCore")
				.constructor0()
				.function("Stop", &GameCore::Stop)
				.function("SetFullscreen", &GameCore::SetFullscreen)
				.function("ToggleFullscreen", &GameCore::ToggleFullscreen);
		}

	protected:
		void recreateWindow();

		boost::shared_ptr<sf::RenderWindow>	mMainWindow;
		boost::shared_ptr<sf::View>			mMainView;

		OptionsManager::Ptr		mOptions;

		RenderManager::Ptr		mRender;
		InputManager::Ptr		mInput;
		ResourceManager::Ptr	mResource;
		LogManager::Ptr			mLog;
		ConsoleManager::Ptr		mExec;
		WorldsManager::Ptr		mWorlds;
		GuiManager::Ptr			mGui;
		ToolManager::Ptr		mTools;
		PhysicsManager::Ptr		mPhysics;
		AudioManager::Ptr		mAudio;

		bool					mIsFullscreen;

		int						mRandomizeSeed;
		static RTID				mLastId;
	};
}

CAMP_AUTO_TYPE(rt::GameCore, &rt::GameCore::RegisterMetaClass)