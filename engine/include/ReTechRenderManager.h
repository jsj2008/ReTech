#ifndef __rtRenderManager_H__
#define __rtRenderManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class WorldObject;

	class RenderManager : public Singleton<RenderManager>
	{
	public:
		RenderManager();
		~RenderManager();

		void Update(float iFrameTime);

		void SetCameraCenter(float iX, float iY);
		void MoverCameraCenter(float iDeltaX, float iDeltaY);
		void SetCameraZoom(float iZoom);

		static bool Sort(WorldObject* iFirst, WorldObject* iSecond);

		void SetRenderStatistics(bool iRenderStatistics);

	protected:
		void renderStatistics();

		bool		mRenderStatistics;
		sf::Text	mStatisticsText;
	};
}

#endif