#ifndef __EditorScreen_H__
#define __EditorScreen_H__

class EditorScreen : public rt::Screen
{
public:
	EditorScreen();
	virtual ~EditorScreen();

	virtual void Pushed();
	virtual void Poped();

	void New();

	void Load();
	void Save();

	bool HandleEvent(const sf::Event& iEvent);

protected:
	rt::World*	mEditingWorld;

	std::string mWorldFileName;

	rt::InputManager::InputHandler mHandler;
};

#endif