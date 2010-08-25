#ifndef __EditorScreen_H__
#define __EditorScreen_H__

class EditorWaypoint;

class EditorScreen : public rt::Screen, public rt::Singleton<EditorScreen>
{
public:
	EditorScreen();
	virtual ~EditorScreen();

	virtual void Pushed();
	virtual void Poped();

	virtual void Update(float iFrameTime);

	void New();

	void Load();
	void Save();

	bool HandleEvent(const sf::Event& iEvent);

	void SetActiveWaypoint(EditorWaypoint* iWaypoint);
	EditorWaypoint* GetActiveWaypoint();
	void ResetActiveWaypoint();

	void SetSpicialMode(bool iActive);
	bool IsSpecialMode();

protected:
	rt::World*		mEditingWorld;

	std::string		mWorldFileName;

	EditorWaypoint*	mActiveWaypoint;
	bool			mIsSpecialMode;

	rt::Line*		mPointerLine;

	rt::InputManager::InputHandler mHandler;
};

#endif