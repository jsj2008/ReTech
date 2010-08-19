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
#include "ReTechScreenManager.h"

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
		ScreenManager		mScreens;

		bool				mIsFullscreen;

		int					mRandomizeSeed;
		static RTID			mLastId;
	};
}

#endif