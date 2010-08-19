#include "GameCommonIncludes.h"
#include "Waypoint.h"

#include "EditorScreen.h"

Waypoint* Waypoint::mSelectedWaypoint = 0;

Waypoint::Waypoint()
	: mDotRadius(8.0f), mCanDrag(false), mWasDragged(false)
{
	mClassName = "Waypoint";

	CreateVarProperty("connections", mConnectedWaypointsIDs);

	mNormalColor = sf::Color(82, 255, 63, 128);
	mHoverColor = sf::Color(82, 0, 63, 128);

	mRenderDot.SetCenter(sf::Vector2f(0.0f, 0.0f), mDotRadius);
	mRenderDot.SetBrush(mNormalColor);
	mRenderDot.SetOutline(1.0f, sf::Color(128, 128, 128, 128));

	mRenderLine.SetBrush(2.0f, sf::Color(255, 255, 0, 128));
}

Waypoint::~Waypoint()
{

}

void Waypoint::Serialize( YAML::Emitter& iEmitter )
{
	//populate IDs vector
	mConnectedWaypointsIDs.clear();
	for(WaypointsVec::const_iterator iter = mConnectedWaypoints.begin(); iter != mConnectedWaypoints.end(); ++iter)
	{
		mConnectedWaypointsIDs.push_back((*iter)->GetUniqueID());
	}

	WorldObject::Serialize(iEmitter);
}

void Waypoint::Fix()
{
	mSelectedWaypoint = 0;

	for(IDsVec::iterator iter = mConnectedWaypointsIDs.begin(); iter != mConnectedWaypointsIDs.end(); ++iter)
	{
		WorldObject* worldObject = mWorld->GetObject(mWorld->ResolveID((*iter)));
		if(worldObject)
		{
			mConnectedWaypoints.insert(static_cast<Waypoint*>(worldObject));
		}
	}
}

void Waypoint::Draw( sf::RenderWindow* iRenderWindow )
{
	mRenderDot.SetPosition(GetPosition());
	mRenderDot.SetScale(GetScale());
	mRenderDot.SetOrigin(GetOrigin());
	mRenderDot.SetRotation(GetRotation());

	mRenderDot.Draw(iRenderWindow);

	for(WaypointsVec::iterator iter = mConnectedWaypoints.begin(); iter != mConnectedWaypoints.end(); ++iter)
	{
		mRenderLine.SetPoints(GetPosition(), (*iter)->GetPosition());
		mRenderLine.Draw(iRenderWindow);
	}
}

bool Waypoint::IsMouseInside( const sf::Vector2f& iMousePos )
{
	return sfm::Length(GetPosition() - iMousePos) < mDotRadius;
}

bool Waypoint::HandleFocusedEvent( const sf::Event& iEvent )
{
	if(iEvent.Type == sf::Event::MouseMoved)
	{
		if(mCanDrag && !EditorScreen::Get()->IsSpecialMode())
		{
			mWasDragged = true;

			SetPosition(static_cast<float>(iEvent.MouseMove.X), static_cast<float>(iEvent.MouseMove.Y));
		}
	}

	if(iEvent.MouseButton.Button == sf::Mouse::Left)
	{
		if(iEvent.Type == sf::Event::MouseButtonPressed)
		{
			mCanDrag = true;
		}
		else if(iEvent.Type == sf::Event::MouseButtonReleased)
		{
			mCanDrag = false;

			if(mWasDragged)
			{
				mWasDragged = false;
			}
			else if(EditorScreen::Get()->IsSpecialMode())
			{
				Waypoint* activeWaypoint = EditorScreen::Get()->GetActiveWaypoint();

 				if(!activeWaypoint)
 				{
 					EditorScreen::Get()->SetActiveWaypoint(this);
 				}
				else if(activeWaypoint != this)
				{
					activeWaypoint->Connect(this);
					Connect(activeWaypoint);
					EditorScreen::Get()->SetActiveWaypoint(this);
				}
			}
		}
	}
	else if(iEvent.MouseButton.Button == sf::Mouse::Right && iEvent.Type == sf::Event::MouseButtonReleased)
	{
		DisconnectAll();

		if(!EditorScreen::Get()->IsSpecialMode())
		{
			mWorld->DestroyObject(this);
		}
	}

	return true;
}

void Waypoint::MouseEnter()
{
	if(mSelectedWaypoint != this)
	{
		mRenderDot.SetBrush(mHoverColor);
	}
}

void Waypoint::MouseLeave()
{
	if(mSelectedWaypoint != this)
	{
		mRenderDot.SetBrush(mNormalColor);
	}
}

void Waypoint::Connect( Waypoint* iWaypoint )
{
	mConnectedWaypoints.insert(iWaypoint);
}

void Waypoint::Disconnect( Waypoint* iWaypoint )
{
	mConnectedWaypoints.erase(iWaypoint);
}

void Waypoint::DisconnectAll()
{
	for(WaypointsVec::const_iterator iter = mConnectedWaypoints.begin(); iter != mConnectedWaypoints.end(); ++iter)
	{
		(*iter)->Disconnect(this);
	}

	mConnectedWaypoints.clear();
}
