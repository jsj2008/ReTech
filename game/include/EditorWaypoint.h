#ifndef __EditorWaypoint_H__
#define __EditorWaypoint_H__

#include "Waypoint.h"

class EditorWaypoint : public Waypoint
{
public:
	EditorWaypoint();
	virtual ~EditorWaypoint();

	virtual void Draw(sf::RenderWindow* iRenderWindow);

	virtual bool IsPointInside(const sf::Vector2f& iMousePos);
	virtual bool HandleFocusedEvent(const sf::Event& iEvent);

	virtual void MouseEnter();
	virtual void MouseLeave();

protected:
	rt::Circle			mRenderDot;
	sf::Color			mNormalColor;
	sf::Color			mHoverColor;

	float				mDotRadius;

	bool				mCanDrag;
	bool				mWasDragged;

	rt::Line			mRenderLine;
};

#endif