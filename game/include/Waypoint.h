#ifndef __Waypoint_H__
#define __Waypoint_H__

class Waypoint : public rt::WorldObject
{
public:
	typedef std::set<Waypoint*>		WaypointsVec;
	typedef std::vector<rt::RTID>	IDsVec;

	Waypoint();

	virtual void Serialize(YAML::Emitter& iEmitter);

	virtual void Fix();

	virtual void Draw(sf::RenderWindow* iRenderWindow);

	virtual bool IsMouseInside(const sf::Vector2f& iMousePos);
	virtual bool HandleFocusedEvent(const sf::Event& iEvent);

	virtual void MouseEnter();
	virtual void MouseLeave();

	void Connect(Waypoint* iWaypoint);
	void Disconnect(Waypoint* iWaypoint);

	void SetColor(const sf::Color& iColor);

protected:
	rt::Circle			mRenderDot;
	sf::Color			mNormalColor;
	sf::Color			mHoverColor;
	sf::Color			mSelectedColor;

	float				mDotRadius;

	rt::Line			mRenderLine;

	WaypointsVec		mConnectedWaypoints;
	IDsVec				mConnectedWaypointsIDs;

	static Waypoint*	mSelectedWaypoint;
};

#endif