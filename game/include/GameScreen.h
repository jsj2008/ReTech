#ifndef __GameScreen_H__
#define __GameScreen_H__

class GameManager;

class GameScreen
{
public:
	GameScreen(GameManager* iManager, const std::string& iLevelName);
	virtual ~GameScreen();

	rt::World* GetWorld(); 

protected:
	GameManager* mManager;
	rt::World*	 mWorld;
};

#endif