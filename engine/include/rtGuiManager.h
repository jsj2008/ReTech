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
	class GuiScreen;

	class GuiManager : public Singleton<GuiManager>
	{
	public:
		typedef std::vector<GuiScreen*>								ScreenVec;
		typedef ScreenVec::iterator									ScreenVecIter;
		typedef std::map<std::string, boost::shared_ptr<GuiScreen>> ScreenMap;
		typedef ScreenMap::iterator									ScreenMapIter;

		typedef boost::shared_ptr<GuiManager>						Ptr;

		GuiManager();
		~GuiManager();

		void Update(float iFrameTime);
		bool HandleEvent(const sf::Event& iEvent);
		void Render();

		sfg::GUI* GetGui();

		void AddScreen(const std::string& iName, GuiScreen* iScreen);

		void ChangeScreen(const std::string& iName);
		void PushScreen(const std::string& iName);
		void PopScreen();
		void ClearScreens();

	protected:
		boost::shared_ptr<sfg::GUI> mGui;

		ScreenMap	mScreens;
		ScreenVec	mScreenStack;
	};
}