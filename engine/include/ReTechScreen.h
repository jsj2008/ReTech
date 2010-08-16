#ifndef __rtScreen_H__
#define __rtScreen_H__

namespace rt
{	
	class ScreenManager;
	class World;

	class Screen
	{
	public:
		Screen(const std::string& iLevelName);
		virtual ~Screen();

		virtual void Pushed();
		virtual void Poped();
		virtual void Paused();
		virtual void Resumed();

		virtual void Update(float iFrameTime);

		World* GetWorld(); 

	protected:
		World*	 mWorld;
	};
}

#endif