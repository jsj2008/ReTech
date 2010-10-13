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

#ifndef __rtGameCore_H__
#define __rtGameCore_H__

#include "ReTechSingleton.h"

#include "ReTechOptionsManager.h"

#include "ReTechRenderManager.h"
#include "ReTechInputManager.h"
#include "ReTechResourceManager.h"
#include "ReTechLogManager.h"
#include "ReTechConsoleManager.h"
#include "ReTechWorldsManager.h"
#include "rtGuiManager.h"

namespace rt
{
	typedef unsigned int RTID;

	class Atom;

	class GameCore : public Singleton<GameCore>
	{
	public:
		GameCore();
		~GameCore();

		void Initialize();

		void Run();
		void Stop();
		void Shutdown();

		RTID CreateUniqueId();

		sf::RenderWindow*	GetMainWindow();
		sf::View*			GetMainView();

		void SetFullscreen(bool iIsFullscreen);
		void ToggleFullscreen();

	protected:
		void recreateWindow();

		boost::shared_ptr<sf::RenderWindow>	mMainWindow;
		boost::shared_ptr<sf::View>			mMainView;

		OptionsManager		mOptionsManager;

		RenderManager		mRender;
		InputManager		mInput;
		ResourceManager		mResource;
		LogManager			mLog;
		ConsoleManager		mExec;
		WorldsManager		mWorlds;
		GuiManager			mGui;

		bool				mIsFullscreen;

		int					mRandomizeSeed;
		static RTID			mLastId;
	};
}

#endif