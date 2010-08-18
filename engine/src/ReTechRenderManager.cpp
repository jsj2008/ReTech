#include "ReTechCommonIncludes.h"
#include "ReTechRenderManager.h"
#include "ReTechWorldObject.h"

URegisterSingleton(RenderManager)

namespace rt
{
	RenderManager::RenderManager()
		: mRenderStatistics(false)
	{
		mStatisticsText.SetFont(sf::Font::GetDefaultFont());
		mStatisticsText.SetCharacterSize(10);
	}

	RenderManager::~RenderManager()
	{
	}

	void RenderManager::Update( float iFrameTime )
	{
 		GameCore::Get()->GetMainWindow()->Clear(sf::Color(0, 0, 0));
 
		mVisibleObjectsCache.clear();
		WorldsManager::Get()->GetVisibleObjects(mVisibleObjectsCache);
 
 		std::sort(mVisibleObjectsCache.begin(), mVisibleObjectsCache.end(), RenderManager::Sort);
 
 		WorldObjectsVec::iterator end = mVisibleObjectsCache.end();
 		for(WorldObjectsVec::iterator iter = mVisibleObjectsCache.begin(); iter != end; ++iter)
 		{
 			(*iter).lock()->Draw(GameCore::Get()->GetMainWindow());
 		}

		if(mRenderStatistics)
		{
			renderStatistics();
		}
 
 		GameCore::Get()->GetMainWindow()->Display();
	}

	bool RenderManager::Sort(boost::weak_ptr<WorldObject> iFirst, boost::weak_ptr<WorldObject> iSecond)
	{
		return iFirst.lock()->LowerThen(iSecond.lock().get());
	}

	void RenderManager::SetCameraCenter( float iX, float iY )
	{
		GameCore::Get()->GetMainView()->SetCenter(iX, iY);
	}

	void RenderManager::MoverCameraCenter( float iDeltaX, float iDeltaY )
	{
		GameCore::Get()->GetMainView()->Move(iDeltaX, iDeltaY);
	}

	void RenderManager::SetCameraZoom( float iZoom )
	{
		GameCore::Get()->GetMainView()->Zoom(iZoom);
	}

	void RenderManager::SetRenderStatistics( bool iRenderStatistics )
	{
		mRenderStatistics = iRenderStatistics;
	}

	const RenderManager::WorldObjectsVec& RenderManager::GetVisibleObjectsCache()
	{
		return mVisibleObjectsCache;
	}

	void RenderManager::renderStatistics()
	{
		sf::String statisticsString = 
			"FPS: " + Poco::NumberFormatter::format(1.0f / GameCore::Get()->GetMainWindow()->GetFrameTime());

		mStatisticsText.SetString(statisticsString);

		GameCore::Get()->GetMainWindow()->Draw(mStatisticsText);
	}
}