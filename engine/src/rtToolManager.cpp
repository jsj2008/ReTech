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

#include "ReTechCommonIncludes.h"
#include "rtToolManager.h"
#include "rtTool.h"

URegisterSingleton(ToolManager)

namespace rt
{
	ToolManager::ToolManager()
	{

	}

	ToolManager::~ToolManager()
	{

	}

	void ToolManager::Update( float iTimeElapsed )
	{
		std::for_each(mTools.begin(), mTools.end(), [iTimeElapsed](boost::shared_ptr<Tool>& iTool)->void
		{
			iTool->Update(iTimeElapsed);
		});
	}

	void ToolManager::Render()
	{
		std::for_each(mTools.begin(), mTools.end(), [](boost::shared_ptr<Tool>& iTool)->void
		{
			iTool->Render();
		});
	}

	bool ToolManager::HandleEvent( const sf::Event& iEvent )
	{
		bool eventHandled = false;

		std::for_each(mTools.begin(), mTools.end(), [&eventHandled, &iEvent](boost::shared_ptr<Tool>& iTool)->void
		{
			if(iTool->HandleEvent(iEvent))
			{
				eventHandled = true;
			}
		});

		return eventHandled;
	}

	void ToolManager::AddTool( Tool* iTool )
	{
		mTools.push_back(boost::shared_ptr<Tool>(iTool));
	}
}