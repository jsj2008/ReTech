#include "ReTechCommonIncludes.h"
#include "ReTechWorld.h"
#include "ReTechWorldObject.h"

namespace rt
{
	World::World(const std::string& iName)
		: mName(iName), mRootObject(new WorldObject()), mIsLoading(false), mIsLoaded(true), mIsVisible(true), mShowAfterLoad(false), 
		mProgress(0.0f), mObjectsData(0), mCurrentObjectIndex(0)
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
 		if(mCurrentObjectIndex < mObjectsData->size())
 		{
			WorldObject* worldObject = static_cast<WorldObject*>(ObjectsFactory::CreateObject((*mObjectsData)[mCurrentObjectIndex]["class"]));
			(*mObjectsData)[mCurrentObjectIndex] >> worldObject;

			AddObject(worldObject);

			++mCurrentObjectIndex;
			mProgress = static_cast<float>(mCurrentObjectIndex) / static_cast<float>(mObjectsData->size());
		}
		else
		{
			mDocument.Clear();
			mObjectsData = 0;

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

			std::ifstream inFile(iFileName.c_str());

			if(inFile.is_open())
			{
				YAML::Parser parser(inFile);
				parser.GetNextDocument(mDocument);

				mObjectsData = &(mDocument["objects"]);

				mShowAfterLoad = iShowAfterLoad;

				mIsLoading = true;
			}
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
		mCurrentObjectIndex = 0;
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