#include "ReTechCommonIncludes.h"
#include "ReTechWorld.h"
#include "ReTechWorldObject.h"

namespace rt
{
	World::World(const std::string& iName)
		: mName(iName), mRootObject(new WorldObject()), mIsLoading(false), mIsLoaded(true), mIsVisible(true), mShowAfterLoad(false)
	{
		mRootObject->SetWorld(this);
	}

	World::~World()
	{
		mRootObject.assign(0);
	}

	void World::AddObject( WorldObject* iObject, WorldObject* iParent )
	{
		iObject->SetWorld(this);

		if(iParent != 0)
		{
			iParent->Attach(iObject);
		}
		else
		{
			mRootObject->Attach(iObject);
		}

		mObjects.push_back(iObject);

		iObject->OnAddToWorld();
	}

	void World::DestroyObject( WorldObject* iObject )
	{
		ObjectsManagedVec::iterator finded = std::find(mObjects.begin(), mObjects.end(), iObject);

		if(finded != mObjects.end())
		{
			(*finded).assign(0);
		}
		else
		{
			LogManager::Get()->Warning("Cannot destroy object. Out of world.");
		}
	}

	void World::Update( float iFrameTime )
	{
		mVisibleObjectsCache.clear();

		if(mIsVisible)
		{
			mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), Poco::SharedPtr<WorldObject>()), mObjects.end());

			for(ObjectsManagedVec::iterator iter = mObjects.begin(); iter != mObjects.end(); ++iter)
			{
				if(!(*iter).isNull())
				{
					if((*iter)->IsEnabled())
					{
						(*iter)->Update(iFrameTime);
					}
					
					if((*iter)->IsVisible())
					{
						mVisibleObjectsCache.push_back((*iter).get());
					}
				}
			}
		}
		else if(mIsLoading)
		{
			ProcessLoad();
		}
	}

	void World::GetVisibleObjects( std::vector<WorldObject*>& iVisibleObjects )
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
				mObjectsIterator->Node() >> worldObject;

				AddObject(worldObject);
			}

			mObjectsIterator->Next();
		}
		else
		{
			mObjectsIterator.assign(0);
			mDocumentIterator.assign(0);

			mIsLoaded = true;
			mIsLoading = false;

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

			mDocumentIterator.assign(new CollectionIterator(iFileName));
			mObjectsIterator.assign(new CollectionIterator(mDocumentIterator->Extract("objects")));

			mShowAfterLoad = iShowAfterLoad;
			mIsLoading = true;
		}
	}

	void World::Unload()
	{
		for(ObjectsManagedVec::iterator iter = mObjects.begin(); iter != mObjects.end(); ++iter)
		{
			if(!(*iter).isNull())
			{
				DestroyObject((*iter));
			}
		}

		mIsLoaded = false;
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
}