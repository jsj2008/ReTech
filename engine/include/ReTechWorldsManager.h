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

#ifndef __rtWorldsManager_H__
#define __rtWorldsManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class World;

	class WorldsManager : public Singleton<WorldsManager>
	{
	public:
		typedef std::list<boost::shared_ptr<World>>			WorldsVec;
		typedef WorldsVec::iterator							WorldsVecIter;
		typedef std::vector<boost::weak_ptr<WorldObject>>	ObjectsVec;
		typedef ObjectsVec::iterator						ObjectsVecIter;

		typedef boost::shared_ptr<WorldsManager>			Ptr;

		class IsNamed
		{
		public:
			IsNamed(const std::string& iName)
				: mName(iName){}

			bool operator()(const boost::shared_ptr<World>& iWorld);

		protected:
			std::string mName;
		};

		WorldsManager();
		~WorldsManager();

		void Update(float iFrameTime);

		World* CreateWorld(const std::string& iName, int iLayer = 0);
		void DestroyWorld(const std::string& iName);

		World* GetWorld(const std::string& iName);

		void GetVisibleObjects(std::vector<boost::weak_ptr<WorldObject>>& iVisibleObjects);

		sf::Vector2f ScreenToWorld(unsigned int iX, unsigned int iY);

	protected:
		WorldsVec mWorlds;

		ObjectsVec mVisibleObjectsCache;
	};
}

#endif