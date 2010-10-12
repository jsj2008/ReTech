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
		typedef std::map<RTID, RTID>						RTIDMap;

		World(const std::string& iName, int iLayer);
		~World();

		void AddObject(WorldObject* iObject);
		void DestroyObject(WorldObject* iObject);
		WorldObject* GetObject(const RTID& iObjectID);

		void QueryObjects(const sf::Vector2f& iPoint, std::vector<WorldObject*>& iObjects);

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

		void AddIDPair(const RTID& iOld, const RTID& iNew);
		RTID ResolveID(const RTID& iOld);

		void FixObjects();

	protected:
		std::string			mName;

		int					mLayer;

		ObjectsManagedVec	mObjects;

		ObjectsWeakVec		mVisibleObjectsCache;

		bool				mIsLoading;
		bool				mIsLoaded;
		bool				mIsVisible;

		bool				mShowAfterLoad;

		RTIDMap				mIDResolveMap;

		boost::shared_ptr<CollectionIterator>	mDocumentIterator;
		boost::shared_ptr<CollectionIterator>	mObjectsIterator;
	};
}

#endif