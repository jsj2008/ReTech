/*
Copyright (c) 2010 Alexander Novitsky                                             

Permission is hereby granted, free of charge, to any person obtaining a copy  
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights  
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     
copies of the Software, and to permit persons to whom the Software is         
furnished to do so, subject to the following conditions:                      

The above copyright notice and this permission notice shall be included in    
all copies or substantial portions of the Software.                           

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     
THE SOFTWARE.
*/

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
			"FPS: " + boost::lexical_cast<std::string>(1.0f / GameCore::Get()->GetMainWindow()->GetFrameTime());

		mStatisticsText.SetString(statisticsString);

		GameCore::Get()->GetMainWindow()->Draw(mStatisticsText);
	}
}