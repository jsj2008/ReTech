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

#ifndef __rtLibraries_H__
#define __rtLibraries_H__

#ifdef _DEBUG
	#pragma comment(lib, "Iphlpapi.lib")
	#pragma comment(lib, "sfml2-audio-s-d.lib")
	#pragma comment(lib, "sfml2-graphics-s-d.lib")
	#pragma comment(lib, "sfml2-network-s-d.lib")
	#pragma comment(lib, "sfml2-system-s-d.lib")
	#pragma comment(lib, "sfml2-window-s-d.lib")
	#pragma comment(lib, "yamlcppd.lib")
	#pragma comment(lib, "SPARK_debug.lib")
	#pragma comment(lib, "SPARK_GL_debug.lib")
	#pragma comment(lib, "SPARK_SFML_debug.lib")
#else
	#pragma comment(lib, "Iphlpapi.lib")
	#pragma comment(lib, "sfml2-audio-s.lib")
	#pragma comment(lib, "sfml2-graphics-s.lib")
	#pragma comment(lib, "sfml2-network-s.lib")
	#pragma comment(lib, "sfml2-system-s.lib")
	#pragma comment(lib, "sfml2-window-s.lib")
	#pragma comment(lib, "yamlcpp.lib")
	#pragma comment(lib, "SPARK.lib")
	#pragma comment(lib, "SPARK_GL.lib")
	#pragma comment(lib, "SPARK_SFML.lib")
#endif

#endif