#ifndef __rtRenderManager_H__
#define __rtRenderManager_H__

namespace rt
{
	class WorldObject;

	class RenderManager
	{
	public:
		RenderManager();
		~RenderManager();

		void Update(float iFrameTime);

		void SetCameraCenter(float iX, float iY);
		void MoverCameraCenter(float iDeltaX, float iDeltaY);
		void SetCameraZoom(float iZoom);

		static bool Sort(WorldObject* iFirst, WorldObject* iSecond);

	protected:
		
	};
}

#endif