#include "ReTechCommonIncludes.h"
#include "ReTechWorld.h"
#include "ReTechWorldObject.h"

namespace rt
{
	World::World(const std::string& iName)
		: mName(iName), mRootObject(new WorldObject()), mIsLoading(false), mIsLoaded(true), mIsVisible(true), mShowAfterLoad(false), 
		mProgress(0.0f), mCurrentChunkIndex(0)
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
 		if(mCurrentChunkIndex < mDataChunks.size())
 		{
			if(mDataChunks[mCurrentChunkIndex].GetName() == "object")
			{
				AddObject(mDataChunks[mCurrentChunkIndex].CreateWorldObject());
			}

			++mCurrentChunkIndex;
			mProgress = static_cast<float>(mCurrentChunkIndex) / static_cast<float>(mDataChunks.size());
		}
		else
		{
			//end loading
			mSerializer.assign(0);
			mDataChunks.clear();

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

			mSerializer.assign(new Serializer());
			mSerializer->SetFile(iFileName);

			if(mSerializer->GetChunk().GetName() != "world")
			{
				LogManager::Get()->Error("Wrong level file. " + iFileName);
			}
			
			if(mSerializer->GetChunk().HasSubChunks())
			{
				mSerializer->GetChunk().GetSubChunks(mDataChunks);
			}

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
		return mProgress;
	}

	std::string World::GetName() const
	{
		return mName;
	}
}