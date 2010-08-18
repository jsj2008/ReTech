#ifndef __rtRenderManager_H__
#define __rtRenderManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class WorldObject;

	class RenderManager : public Singleton<RenderManager>
	{
	public:
		typedef std::vector<boost::weak_ptr<WorldObject>> WorldObjectsVec;

		RenderManager();
		~RenderManager();

		void Update(float iFrameTime);

		void SetCameraCenter(float iX, float iY);
		void MoverCameraCenter(float iDeltaX, float iDeltaY);
		void SetCameraZoom(float iZoom);

		static bool Sort(boost::weak_ptr<WorldObject> iFirst, boost::weak_ptr<WorldObject> iSecond);

		void SetRenderStatistics(bool iRenderStatistics);

		const WorldObjectsVec& GetVisibleObjectsCache();

	protected:
		void renderStatistics();

		bool			mRenderStatistics;
		sf::Text		mStatisticsText;

		WorldObjectsVec	mVisibleObjectsCache;
	};
}

#endif