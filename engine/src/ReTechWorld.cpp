#include "ReTechCommonIncludes.h"
#include "ReTechWorld.h"
#include "ReTechWorldObject.h"

namespace rt
{
	World::World(const std::string& iName, int iLayer)
		: mName(iName), mLayer(iLayer), mIsLoading(false), mIsLoaded(true), mIsVisible(true), mShowAfterLoad(false)
	{
	}

	World::~World()
	{
	}

	void World::AddObject( WorldObject* iObject )
	{
		iObject->SetWorld(this);

		mObjects.push_back(boost::shared_ptr<WorldObject>(iObject));
	}

	void World::DestroyObject( WorldObject* iObject )
	{
		ObjectsManagedVec::iterator finded = std::find(mObjects.begin(), mObjects.end(), boost::shared_ptr<WorldObject>(iObject));

		if(finded != mObjects.end())
		{
			(*finded).reset(static_cast<WorldObject*>(0));
		}
		else
		{
			LogManager::Get()->Warning("Cannot destroy object. Out of world.");
		}
	}

	WorldObject* World::GetObject( const RTID& iObjectID )
	{
		for(ObjectsManagedVec::iterator iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if((*iter)->GetUniqueID() == iObjectID)
			{
				return (*iter).get();
			}
		}

		return 0;
	}

	void World::Update( float iFrameTime )
	{
		mVisibleObjectsCache.clear();

		if(mIsVisible)
		{
			mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), boost::shared_ptr<WorldObject>()), mObjects.end());

			for(ObjectsManagedVec::iterator iter = mObjects.begin(); iter != mObjects.end(); ++iter)
			{
				if((*iter))
				{
					if((*iter)->IsEnabled())
					{
						(*iter)->Update(iFrameTime);
					}
					
					if((*iter)->IsVisible())
					{
						mVisibleObjectsCache.push_back((*iter));
					}
				}
			}
		}
		else if(mIsLoading)
		{
			ProcessLoad();
		}
	}

	void World::GetVisibleObjects( std::vector<boost::weak_ptr<WorldObject>>& iVisibleObjects )
	{
		iVisibleObjects.insert(iVisibleObjects.end(), mVisibleObjectsCache.begin(), mVisibleObjectsCache.end());
	}

	void World::ProcessLoad()
	{
 		if(!mObjectsIterator->End())
 		{
			std::string className;
			mObjectsIterator->SafeGet("class", className);

			if(!className.empty())
			{
				WorldObject* worldObject = static_cast<WorldObject*>(ObjectsFactory::CreateObject(className));
				AddObject(worldObject);
				mObjectsIterator->Node() >> worldObject;

				//AddObject(worldObject);
			}

			mObjectsIterator->Next();
		}
		else
		{
			mObjectsIterator.reset(static_cast<CollectionIterator*>(0));
			mDocumentIterator.reset(static_cast<CollectionIterator*>(0));

			mIsLoaded = true;
			mIsLoading = false;

			FixObjects();

			if(mShowAfterLoad)
			{
				SetVisible(true);
			}
		}
	}

	bool World::IsLoaded()
	{
		return mIsLoaded;
	}

	bool World::IsVisible()
	{
		return mIsVisible;
	}

	void World::Load( const std::string& iFileName, bool iShowAfterLoad /*= false*/ )
	{
		Unload();

		if(!mIsLoaded)
		{
			mIsVisible = false;

			mDocumentIterator.reset(new CollectionIterator(iFileName));
			mObjectsIterator.reset(new CollectionIterator(mDocumentIterator->Extract("objects")));

			mShowAfterLoad = iShowAfterLoad;
			mIsLoading = true;
		}
	}

	void World::Unload()
	{
		for(ObjectsManagedVec::iterator iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if((*iter))
			{
				DestroyObject((*iter).get());
			}
		}

		mIDResolveMap.clear();

		mIsLoaded = false;
	}

	void World::Save( const std::string& iFileName )
	{
		YAML::Emitter myEmitter;

		myEmitter << YAML::BeginMap;
		myEmitter << YAML::Key << "objects";
		myEmitter << YAML::Value;

		myEmitter << YAML::BeginSeq;

		for(ObjectsManagedVec::iterator iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			myEmitter << YAML::BeginMap;
			(*iter)->Serialize(myEmitter);
			myEmitter << YAML::EndMap;
		}

		myEmitter << YAML::EndSeq;
		myEmitter << YAML::EndMap;

		std::ofstream myFile(iFileName.c_str());

		myFile << myEmitter.c_str();

		myFile.flush();
		myFile.close();
	}

	void World::SetVisible( bool iVisible )
	{
		mIsVisible = iVisible;
	}

	float World::GetProgress()
	{
		return mObjectsIterator->Progress();
	}

	std::string World::GetName() const
	{
		return mName;
	}

	int World::GetLayer() const
	{
		return mLayer;
	}

	void World::SetLayer( int iLayer )
	{
		mLayer = iLayer;
	}

	void World::AddIDPair( const RTID& iOld, const RTID& iNew )
	{
		if(mIDResolveMap.find(iOld) != mIDResolveMap.end())
		{
			LogManager::Get()->Warning("ID pair already exists");
			return;
		}

		mIDResolveMap[iOld] = iNew;
	}

	rt::RTID World::ResolveID( const RTID& iOld )
	{
		if(mIDResolveMap.find(iOld) == mIDResolveMap.end())
		{
			LogManager::Get()->Warning("ID pair dont exists");
			return -1;
		}

		return mIDResolveMap[iOld];
	}

	void World::FixObjects()
	{
		for(ObjectsManagedVec::iterator iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if((*iter))
			{
				(*iter)->Fix();
			}
		}
	}
}