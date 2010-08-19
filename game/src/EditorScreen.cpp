#include "GameCommonIncludes.h"
#include "EditorScreen.h"

#include "Waypoint.h"

EditorScreen::EditorScreen()
	: Screen(""), mEditingWorld(0)
{
	rt::ConsoleManager::Get()->RegisterExec("test_save", &EditorScreen::Save, this);
	rt::InputManager::Get()->RegisterBind(sf::Key::S, "test_save");
	rt::ConsoleManager::Get()->RegisterExec("test_load", &EditorScreen::Load, this);
	rt::InputManager::Get()->RegisterBind(sf::Key::L, "test_load");
	rt::ConsoleManager::Get()->RegisterExec("test_new", &EditorScreen::New, this);
	rt::InputManager::Get()->RegisterBind(sf::Key::N, "test_new");

	mEditingWorld = rt::WorldsManager::Get()->CreateWorld("Editor");

	mHandler = rt::InputManager::MakeHandler(&EditorScreen::HandleEvent, this);
	rt::InputManager::Get()->RegisterHandler(&mHandler);

	mWorldFileName = "test.world";
}

EditorScreen::~EditorScreen()
{
	rt::WorldsManager::Get()->DestroyWorld("Editor");
	rt::InputManager::Get()->UnregisterHandler(&mHandler);
}

void EditorScreen::Pushed()
{
}

void EditorScreen::Poped()
{

}

void EditorScreen::New()
{
	rt::WorldsManager::Get()->DestroyWorld("Editor");
	mEditingWorld = rt::WorldsManager::Get()->CreateWorld("Editor");
	mWorldFileName = "test.world";
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
		Waypoint* newWaypoint = new Waypoint();
		newWaypoint->SetPosition(static_cast<float>(iEvent.MouseButton.X), static_cast<float>(iEvent.MouseButton.Y));

		mEditingWorld->AddObject(newWaypoint);

		return true;
	}

	return false;
}
