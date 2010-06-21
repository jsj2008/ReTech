#include "ReTechCommonIncludes.h"
#include "ReTechRenderManager.h"
#include "ReTechWorldObject.h"

namespace rt
{
	RenderManager::RenderManager()
	{
	}

	RenderManager::~RenderManager()
	{
	}

	void RenderManager::Update( float iFrameTime )
	{
 		GameCore::Get()->GetMainWindow()->Clear(sf::Color(0, 0, 0));
 
 		std::vector<WorldObject*> visibleObjects;

		WorldsManager::Get()->GetVisibleObjects(visibleObjects);
 
 		std::sort(visibleObjects.begin(), visibleObjects.end(), RenderManager::Sort);
 
 		std::vector<WorldObject*>::iterator end = visibleObjects.end();
 		for(std::vector<WorldObject*>::iterator iter = visibleObjects.begin(); iter != end; ++iter)
 		{
 			(*iter)->Draw(GameCore::Get()->GetMainWindow());
 		}
 
 		GameCore::Get()->GetMainWindow()->Display();
	}

	bool RenderManager::Sort(WorldObject* iFirst, WorldObject* iSecond)
	{
		return iFirst->LowerThen(iSecond);
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
}