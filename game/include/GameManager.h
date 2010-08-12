#ifndef __GameManager_H__
#define __GameManager_H__

class GameScreen;

class GameManager : public rt::WorldObject
{
public:
	typedef std::map<std::string, Poco::SharedPtr<GameScreen>> ScreensMap;

	GameManager();
	~GameManager();

	virtual void Update(float iFrameTime);

	void ChangeScreen(const std::string& iScreenName);

protected:
	Poco::SharedPtr<GameScreen> mLoaderScreen;
	GameScreen* mActiveScreen;

	ScreensMap mScreens;
};

#endif