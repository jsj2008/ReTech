#ifndef __GameManager_H__
#define __GameManager_H__

class GameScreen;

class GameManager : public rt::WorldObject
{
public:
	typedef std::map<std::string, Poco::SharedPtr<GameScreen>>	ScreensMap;
	typedef std::vector<GameScreen*>							ScreenStack;

	GameManager();
	~GameManager();

	virtual void Update(float iFrameTime);

	void PushScreen(const std::string& iScreenName);
	void PopScreen();

	void ChangeScreen(const std::string& iScreenName);

	void ClearScreens();

protected:
	Poco::SharedPtr<GameScreen> mLoaderScreen;
	ScreenStack					mScreenStack;

	ScreensMap					mScreens;
};

#endif