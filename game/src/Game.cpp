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

#include "GameCommonIncludes.h"
#include "GameLibraries.h"

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
	rt::GameCore gameCore;

	rt::OptionsManager::Get()->GetOption("title") = std::string("ReTech Engine v 0.3.0");
	rt::OptionsManager::Get()->GetOption("width") = 1280;
	rt::OptionsManager::Get()->GetOption("height") = 720;
	rt::OptionsManager::Get()->GetOption("bpp") = 32;
	rt::OptionsManager::Get()->GetOption("media_dir") = std::string("./media/");
	rt::OptionsManager::Get()->GetOption("gui_skin") = std::string("skins/default.skin");

	gameCore.Initialize();

	rt::RenderManager::Get()->SetRenderStatistics(true);

	gameCore.Run();

	gameCore.Shutdown();

	return EXIT_SUCCESS;
}