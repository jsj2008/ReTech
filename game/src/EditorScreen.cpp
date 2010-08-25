#include "GameCommonIncludes.h"
#include "EditorScreen.h"

#include "EditorWaypoint.h"

URegisterSingleton(EditorScreen)

EditorScreen::EditorScreen()
	: Screen(""), mEditingWorld(0), mActiveWaypoint(0), mIsSpecialMode(false)
{
	rt::ConsoleManager::Get()->RegisterExec("test_save", &EditorScreen::Save, this);
	rt::InputManager::Get()->RegisterBind(sf::Key::S, "test_save");
	rt::ConsoleManager::Get()->RegisterExec("test_load", &EditorScreen::Load, this);
	rt::InputManager::Get()->RegisterBind(sf::Key::L, "test_load");
	rt::ConsoleManager::Get()->RegisterExec("test_new", &EditorScreen::New, this);
	rt::InputManager::Get()->RegisterBind(sf::Key::N, "test_new");

	rt::ConsoleManager::Get()->RegisterExec("special_mode", &EditorScreen::SetSpicialMode, this);
	rt::InputManager::Get()->RegisterBind(sf::Key::LControl, "special_mode");

	mEditingWorld = rt::WorldsManager::Get()->CreateWorld("Editor");

	mHandler = rt::InputManager::MakeHandler(&EditorScreen::HandleEvent, this);
	rt::InputManager::Get()->RegisterHandler(&mHandler);

	mPointerLine = new rt::Line();
	mPointerLine->SetBrush(2.0f, sf::Color(0, 255, 0, 128));
	mPointerLine->SetVisible(false);

	mWorld->AddObject(mPointerLine);

	rt::ObjectsFactory::AddRedirect("Waypoint", "EditorWaypoint");

	mWorldFileName = "test.world";
}

EditorScreen::~EditorScreen()
{
	rt::WorldsManager::Get()->DestroyWorld("Editor");
	rt::InputManager::Get()->UnregisterHandler(&mHandler);

	rt::ObjectsFactory::RemoveRedirect("Waypoint");
}

void EditorScreen::Pushed()
{
}

void EditorScreen::Poped()
{

}

void EditorScreen::Update( float iFrameTime )
{
	if(mActiveWaypoint)
	{
		mPointerLine->SetPoints(mActiveWaypoint->GetPosition(), rt::InputManager::Get()->GetMousePosition());
	}
	else
	{
		mPointerLine->SetPoints(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f));
	}	
}

void EditorScreen::New()
{
	rt::WorldsManager::Get()->DestroyWorld("Editor");
	mEditingWorld = rt::WorldsManager::Get()->CreateWorld("Editor");
	mWorldFileName = "test.world";

	ResetActiveWaypoint();
}

void EditorScreen::Load()
{
	if(Poco::Path(mWorldFileName).isFile())
	{
		mEditingWorld->Load(mWorldFileName, true);
	}
}

void EditorScreen::Save()
{
	if(mEditingWorld->IsLoaded())
	{
		mEditingWorld->Save(mWorldFileName);
	}
}

bool EditorScreen::HandleEvent( const sf::Event& iEvent )
{
	if(iEvent.Type == sf::Event::MouseButtonReleased && iEvent.MouseButton.Button == sf::Mouse::Left)
	{
		if(!mIsSpecialMode || mActiveWaypoint)
		{
			EditorWaypoint* newWaypoint = new EditorWaypoint();
			newWaypoint->SetPosition(static_cast<float>(iEvent.MouseButton.X), static_cast<float>(iEvent.MouseButton.Y));

			mEditingWorld->AddObject(newWaypoint);

			if(mIsSpecialMode)
			{
				mActiveWaypoint->Connect(newWaypoint);
				newWaypoint->Connect(mActiveWaypoint);

				SetActiveWaypoint(newWaypoint);
			}
		}

		return true;
	}

	return false;
}

void EditorScreen::SetActiveWaypoint( EditorWaypoint* iWaypoint )
{
	mActiveWaypoint = iWaypoint;
}

EditorWaypoint* EditorScreen::GetActiveWaypoint()
{
	return mActiveWaypoint;
}

void EditorScreen::ResetActiveWaypoint()
{
	mActiveWaypoint = 0;
}

void EditorScreen::SetSpicialMode( bool iActive )
{
	mIsSpecialMode = iActive;

	mPointerLine->SetVisible(iActive);

	if(!iActive)
	{
		ResetActiveWaypoint();
	}
}

bool EditorScreen::IsSpecialMode()
{
	return mIsSpecialMode;
}