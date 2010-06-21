#include "ReTechCommonIncludes.h"
#include "ReTechGameCore.h"

#include "ReTechImage.h"
#include "ReTechFont.h"
#include "ReTechSequence.h"

#include "ReTechContainer.h"
#include "ReTechSprite.h"
#include "ReTechAnimation.h"
#include "ReTechButton.h"
#include "ReTechText.h"

URegisterSingleton(GameCore)

int rt::GameCore::mLastId = 0;

namespace rt
{
	GameCore::GameCore()
	{

	}

	GameCore::~GameCore()
	{

	}

	void GameCore::Initialize()
	{
		int width = OptionsManager::Get()->GetOption("width").ToInt();
		int height = OptionsManager::Get()->GetOption("height").ToInt();

		mMainWindow.assign(new sf::RenderWindow(sf::VideoMode(width, height, OptionsManager::Get()->GetOption("bpp").ToInt()), 
			OptionsManager::Get()->GetOption("title").ToString()));
		mMainView.assign(new sf::View(sf::Vector2f(width * 0.5f, height * 0.5f), 
			sf::Vector2f(static_cast<float>(width), static_cast<float>(height))));

		mMainWindow->SetView(*mMainView);

		mRandomizeSeed = (int)time(0);

		mLog.Initialize();

		//Register objects to factory
		URegisterObject(Image);
		URegisterObject(Font);
		URegisterObject(Sequence);
		URegisterObject(Container);
		URegisterObject(Sprite);
		URegisterObject(Animation);
		URegisterObject(Button);
		URegisterObject(Text);

		//Register resource classes
		mResource.RegisterExtension("tga", "Image");
		mResource.RegisterExtension("png", "Image");
		mResource.RegisterExtension("ttf", "Font");
		mResource.RegisterExtension("seq", "Sequence");

		mResource.CreateResources();

		//Register execs
		mExec.RegisterExec("quit", &GameCore::Stop, this);

		LogManager::Get()->Notice("GameCore initialized.");
	}

	void GameCore::Run()
	{
		sf::Randomizer::SetSeed(mRandomizeSeed);

		while (mMainWindow->IsOpened())
		{
			float frameTime = mMainWindow->GetFrameTime();

			mInput.Update(frameTime);
			mWorlds.Update(frameTime);
			mRender.Update(frameTime);
		}
	}

	void GameCore::Stop()
	{
		mMainWindow->Close();
	}

	void GameCore::Shutdown()
	{
	}

	int GameCore::CreateUniqueId()
	{
		return mLastId++;
	}

	sf::RenderWindow* GameCore::GetMainWindow()
	{
		return mMainWindow.get();
	}

	sf::View* GameCore::GetMainView()
	{
		return mMainView.get();
	}
}