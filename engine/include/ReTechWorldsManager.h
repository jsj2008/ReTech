#ifndef __rtWorldsManager_H__
#define __rtWorldsManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class World;

	class WorldsManager : public Singleton<WorldsManager>
	{
	public:
		typedef std::list<boost::shared_ptr<World>>			WorldsVec;
		typedef std::vector<boost::weak_ptr<WorldObject>>	ObjectsVec;

		class IsNamed
		{
		public:
			IsNamed(const std::string& iName)
				: mName(iName){}

			bool operator()(const boost::shared_ptr<World>& iWorld);

		protected:
			std::string mName;
		};

		WorldsManager();
		~WorldsManager();

		void Update(float iFrameTime);

		World* CreateWorld(const std::string& iName, int iLayer = 0);
		void DestroyWorld(const std::string& iName);

		World* GetWorld(const std::string& iName);

		void GetVisibleObjects(std::vector<boost::weak_ptr<WorldObject>>& iVisibleObjects);

		sf::Vector2f ScreenToWorld(unsigned int iX, unsigned int iY);

	protected:
		WorldsVec mWorlds;

		ObjectsVec mVisibleObjectsCache;
	};
}

#endif