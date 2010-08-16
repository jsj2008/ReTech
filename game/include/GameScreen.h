#ifndef __GameScreen_H__
#define __GameScreen_H__

class GameManager;

class GameScreen
{
public:
	GameScreen(GameManager* iManager, const std::string& iLevelName);
	virtual ~GameScreen();

	virtual void Pushed();
	virtual void Poped();
	virtual void Paused();
	virtual void Resumed();

	virtual void Update(float iFrameTime);

	rt::World* GetWorld(); 

protected:
	GameManager* mManager;
	rt::World*	 mWorld;
};

#endif