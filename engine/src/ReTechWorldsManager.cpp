#include "ReTechCommonIncludes.h"
#include "ReTechWorldsManager.h"
#include "ReTechGameCore.h"
#include "ReTechWorld.h"

URegisterSingleton(WorldsManager)

namespace rt
{
	WorldsManager::WorldsManager()
	{

	}

	WorldsManager::~WorldsManager()
	{

	}

	void WorldsManager::Update( float iFrameTime )
	{
		mVisibleObjectsCache.clear();

		mWorlds.erase(std::remove(mWorlds.begin(), mWorlds.end(), boost::shared_ptr<World>()), mWorlds.end());

		for(WorldsVec::iterator iter = mWorlds.begin(); iter != mWorlds.end(); ++iter)
		{
			if((*iter))
			{
				(*iter)->Update(iFrameTime);

				(*iter)->GetVisibleObjects(mVisibleObjectsCache);
			}
		}
	}

	World* WorldsManager::CreateWorld( const std::string& iName, int iLayer )
	{
		if(GetWorld(iName) != 0)
		{
			LogManager::Get()->Warning("World " + iName + " already exist.");
			return 0;
		}
		mWorlds.push_back(boost::shared_ptr<World>(new World(iName, iLayer)));
		
		return mWorlds.back().get();
	}

	void WorldsManager::DestroyWorld( const std::string& iName )
	{
		WorldsVec::iterator finded = std::find_if(mWorlds.begin(), mWorlds.end(), IsNamed(iName));
		if(finded == mWorlds.end())
		{
			LogManager::Get()->Warning("World " + iName + " doesnt exist.");
			return;
		}

		(*finded).reset(static_cast<World*>(0));
	}

	World* WorldsManager::GetWorld( const std::string& iName )
	{
		WorldsVec::iterator finded = std::find_if(mWorlds.begin(), mWorlds.end(), IsNamed(iName));
		
		if(finded != mWorlds.end())
		{
			return (*finded).get();
		}

		return 0;
	}

	void WorldsManager::GetVisibleObjects( std::vector<boost::weak_ptr<WorldObject>>& iVisibleObjects )
	{
		iVisibleObjects.swap(mVisibleObjectsCache);
	}

	sf::Vector2f WorldsManager::ScreenToWorld( unsigned int iX, unsigned int iY )
	{
		return GameCore::Get()->GetMainWindow()->ConvertCoords(iX, iY);
	}

	bool WorldsManager::IsNamed::operator()( const boost::shared_ptr<World>& iWorld )
	{
		return !iWorld ? false : iWorld->GetName() == mName;
	}
}