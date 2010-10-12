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

#ifndef __rtScreenManager_H__
#define __rtScreenManager_H__

#include "ReTechSingleton.h"

namespace rt
{
	class Screen;

	class ScreenManager : public Singleton<ScreenManager>
	{
	public:
		typedef std::map<std::string, boost::shared_ptr<Screen>>	ScreensMap;
		typedef std::vector<Screen*>							ScreenStack;

		ScreenManager();
		~ScreenManager();

		void AddScreen(const std::string& iScreenName, Screen* iScreen);

		virtual void Update(float iFrameTime);

		void PushScreen(const std::string& iScreenName);
		void PopScreen();

		void ChangeScreen(const std::string& iScreenName);

		void ClearScreens();

	protected:
		ScreenStack	mScreenStack;

		ScreensMap	mScreens;
	};
}

#endif