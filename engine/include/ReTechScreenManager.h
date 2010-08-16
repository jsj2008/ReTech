#ifndef __rtScreenManager_H__
#define __rtScreenManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class Screen;

	class ScreenManager : public Singleton<ScreenManager>
	{
	public:
		typedef std::map<std::string, Poco::SharedPtr<Screen>>	ScreensMap;
		typedef std::vector<Screen*>							ScreenStack;

		ScreenManager();
		~ScreenManager();

		void AddScreen(const std::string& iScreenName, Screen* iScreen);

		virtual void Update(float iFrameTime);

		void PushScreen(const std::string& iScreenName);
		void PopScreen();

		void ChangeScreen(const std::string& iScreenName);

		void ClearScreens();

	protected:
		ScreenStack	mScreenStack;

		ScreensMap	mScreens;
	};
}

#endif