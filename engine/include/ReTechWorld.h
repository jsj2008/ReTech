#ifndef __rtWorld_H__
#define __rtWorld_H__

#include "ReTechCollectionIterator.h"

namespace rt
{
	class World
	{
	public:
		typedef std::list<boost::shared_ptr<WorldObject>>	ObjectsManagedVec;
		typedef std::vector<boost::weak_ptr<WorldObject>>	ObjectsWeakVec;

		World(const std::string& iName, int iLayer);
		~World();

		void AddObject(WorldObject* iObject);
		void DestroyObject(WorldObject* iObject);

		void Update(float iFrameTime);

		void GetVisibleObjects(std::vector<boost::weak_ptr<WorldObject>>& iVisibleObjects);

		void ProcessLoad();

		bool IsLoaded();
		bool IsVisible();

		void Load(const std::string& iFileName, bool iShowAfterLoad = false);
		void Unload();

		void Save(const std::string& iFileName);

		void SetVisible(bool iActivated);

		float GetProgress();

		std::string GetName() const;

		int GetLayer() const;
		void SetLayer(int iLayer);

	protected:
		std::string			mName;

		int					mLayer;

		ObjectsManagedVec	mObjects;

		ObjectsWeakVec		mVisibleObjectsCache;

		bool				mIsLoading;
		bool				mIsLoaded;
		bool				mIsVisible;

		bool				mShowAfterLoad;

		boost::shared_ptr<CollectionIterator>	mDocumentIterator;
		boost::shared_ptr<CollectionIterator>	mObjectsIterator;
	};
}

#endif