#include "GameCommonIncludes.h"
#include "EditorWaypoint.h"

#include "EditorScreen.h"

EditorWaypoint::EditorWaypoint()
: mDotRadius(8.0f), mCanDrag(false), mWasDragged(false)
{
	mNormalColor = sf::Color(82, 255, 63, 128);
	mHoverColor = sf::Color(82, 0, 63, 128);

	mRenderDot.SetCenter(sf::Vector2f(0.0f, 0.0f), mDotRadius);
	mRenderDot.SetBrush(mNormalColor);
	mRenderDot.SetOutline(1.0f, sf::Color(128, 128, 128, 128));

	mRenderLine.SetBrush(2.0f, sf::Color(255, 255, 0, 128));
}

EditorWaypoint::~EditorWaypoint()
{

}

void EditorWaypoint::Draw( sf::RenderWindow* iRenderWindow )
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

bool EditorWaypoint::IsPointInside( const sf::Vector2f& iMousePos )
{
	return sfm::Length(GetPosition() - iMousePos) < mDotRadius;
}

bool EditorWaypoint::HandleFocusedEvent( const sf::Event& iEvent )
{
	if(iEvent.Type == sf::Event::MouseMoved)
	{
		if(mCanDrag && !EditorScreen::Get()->IsSpecialMode())
		{
			mWasDragged = true;

			SetPosition(static_cast<float>(iEvent.MouseMove.X), static_cast<float>(iEvent.MouseMove.Y));
		}

		return true;
	}

	if(iEvent.MouseButton.Button == sf::Mouse::Left)
	{
		if(iEvent.Type == sf::Event::MouseButtonPressed)
		{
			mCanDrag = true;
			rt::InputManager::Get()->SetFocusLock(true);
		}
		else if(iEvent.Type == sf::Event::MouseButtonReleased)
		{
			mCanDrag = false;
			rt::InputManager::Get()->SetFocusLock(false);

			if(mWasDragged)
			{
				mWasDragged = false;

				std::vector<WorldObject*> objectsInPlace;
				mWorld->QueryObjects(sf::Vector2f(static_cast<float>(iEvent.MouseButton.X), static_cast<float>(iEvent.MouseButton.Y)), objectsInPlace);

				if(!objectsInPlace.empty())
				{
					for(std::vector<WorldObject*>::iterator iter = objectsInPlace.begin(); iter != objectsInPlace.end(); ++iter)
					{
						if((*iter) != this && (*iter)->GetClassName() == "Waypoint")
						{
							static_cast<EditorWaypoint*>((*iter))->FuseConnections(mConnectedWaypoints);
							DisconnectAll();
							mWorld->DestroyObject(this);
							break;
						}
					}
				}
			}
			else if(EditorScreen::Get()->IsSpecialMode())
			{
				EditorWaypoint* activeWaypoint = EditorScreen::Get()->GetActiveWaypoint();

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

		return true;
	}
	else if(iEvent.MouseButton.Button == sf::Mouse::Right && iEvent.Type == sf::Event::MouseButtonReleased && !mCanDrag)
	{
		DisconnectAll();

		if(!EditorScreen::Get()->IsSpecialMode())
		{
			mWorld->DestroyObject(this);
		}

		return true;
	}

	return false;
}

void EditorWaypoint::MouseEnter()
{
	if(EditorScreen::Get()->GetActiveWaypoint() != this)
	{
		mRenderDot.SetBrush(mHoverColor);
	}
}

void EditorWaypoint::MouseLeave()
{
	if(EditorScreen::Get()->GetActiveWaypoint() != this)
	{
		mRenderDot.SetBrush(mNormalColor);
	}
}