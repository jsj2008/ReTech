#ifndef __rtWorld_H__
#define __rtWorld_H__

namespace rt
{
	class World
	{
	public:
		typedef std::list<Poco::SharedPtr<WorldObject>>	ObjectsManagedVec;
		typedef std::vector<WorldObject*>				ObjectsVec;

		World(const std::string& iName);
		~World();

		void AddObject(WorldObject* iObject, WorldObject* iParent = 0);
		void DestroyObject(WorldObject* iObject);

		void Update(float iFrameTime);

		void GetVisibleObjects(std::vector<WorldObject*>& iVisibleObjects);

		void ProcessLoad();

		bool IsLoaded();
		bool IsVisible();

		void Load(const std::string& iFileName, bool iShowAfterLoad = false);
		void Unload();

		void SetVisible(bool iActivated);

		float GetProgress();

		std::string GetName() const;

	protected:
		std::string			mName;

		ObjectsManagedVec	mObjects;

		ObjectsVec			mVisibleObjectsCache;

		Poco::SharedPtr<WorldObject> mRootObject;	

		bool				mIsLoading;
		bool				mIsLoaded;
		bool				mIsVisible;

		bool				mShowAfterLoad;

		float				mProgress;

		YAML::Node			mDocument;
		const YAML::Node*	mObjectsData;
		int					mCurrentObjectIndex;
	};
}

#endif