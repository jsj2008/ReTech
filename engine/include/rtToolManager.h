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

#pragma once

#include "rtSingleton.h"

namespace rt
{
	class Tool;

	class ToolManager : public Singleton<ToolManager>
	{
	public:
		typedef std::map<std::string, boost::shared_ptr<Tool>>	ToolMap;
		typedef ToolMap::iterator								ToolMapIter;

		typedef boost::shared_ptr<ToolManager>			Ptr;

		ToolManager();
		~ToolManager();

		void Update(float iTimeElapsed);
		void Render();
		bool HandleEvent(const sf::Event& iEvent);

		void AddTool(const std::string& iToolName, Tool* iTool);

		void ToggleTool(const std::string& iToolName);

		static void RegisterMetaClass()
		{
			camp::Class::declare<ToolManager>("ToolManager")
				.function("ToggleTool", &ToolManager::ToggleTool);
		}

	protected:
		ToolMap	mTools;
	};
}

CAMP_AUTO_TYPE(rt::ToolManager, &rt::ToolManager::RegisterMetaClass)