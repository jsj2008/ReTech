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

		mWorlds.erase(std::remove(mWorlds.begin(), mWorlds.end(), Poco::SharedPtr<World>()), mWorlds.end());

		for(WorldsVec::iterator iter = mWorlds.begin(); iter != mWorlds.end(); ++iter)
		{
			if(!(*iter).isNull())
			{
				(*iter)->Update(iFrameTime);

				(*iter)->GetVisibleObjects(mVisibleObjectsCache);
			}
		}
	}

	World* WorldsManager::CreateWorld( const std::string& iName )
	{
		if(GetWorld(iName) != 0)
		{
			LogManager::Get()->Warning("World " + iName + " already exist.");
			return 0;
		}
		mWorlds.push_back(new World(iName));
		
		return mWorlds.back();
	}

	void WorldsManager::DestroyWorld( const std::string& iName )
	{
		WorldsVec::iterator finded = std::find_if(mWorlds.begin(), mWorlds.end(), IsNamed(iName));
		if(finded == mWorlds.end())
		{
			LogManager::Get()->Warning("World " + iName + " doesnt exist.");
			return;
		}

		(*finded).assign(0);
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

	void WorldsManager::GetVisibleObjects( std::vector<WorldObject*>& iVisibleObjects )
	{
		iVisibleObjects.swap(mVisibleObjectsCache);
	}

	sf::Vector2f WorldsManager::ScreenToWorld( unsigned int iX, unsigned int iY )
	{
		return GameCore::Get()->GetMainWindow()->ConvertCoords(iX, iY);
	}

	bool WorldsManager::IsNamed::operator()( const Poco::SharedPtr<World>& iWorld )
	{
		return iWorld.isNull() ? false : iWorld->GetName() == mName;
	}
}