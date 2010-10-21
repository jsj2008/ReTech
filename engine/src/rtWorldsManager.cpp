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

#include "rtCommonIncludes.h"
#include "rtWorldsManager.h"
#include "rtGameCore.h"
#include "rtWorld.h"

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
			ULogWarning("World " + iName + " already exist.");
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
			ULogWarning("World " + iName + " doesnt exist.");
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