#include "GameCommonIncludes.h"
#include "EditorScreen.h"

EditorScreen::EditorScreen()
	: Screen("./data/worlds/main_menu_screen.world") 
{
	rt::ConsoleManager::Get()->RegisterExec("test_save", &EditorScreen::Save, this);
	rt::InputManager::Get()->RegisterBind(sf::Key::A, "test_save");
}

EditorScreen::~EditorScreen()
{

}

void EditorScreen::Pushed()
{
}

void EditorScreen::Poped()
{

}

void EditorScreen::Save()
{
	mWorld->Save("test.world");
}