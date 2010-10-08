#ifndef __rtLibraries_H__
#define __rtLibraries_H__

#ifdef _DEBUG
	//#pragma comment(lib, "Iphlpapi.lib")
	#pragma comment(lib, "sfml2-audio-d.lib")
	#pragma comment(lib, "sfml2-graphics-d.lib")
	#pragma comment(lib, "sfml2-network-d.lib")
	#pragma comment(lib, "sfml2-system-d.lib")
	#pragma comment(lib, "sfml2-window-d.lib")
	#pragma comment(lib, "yamlcppd.lib")
	#pragma comment(lib, "SPARK_debug.lib")
	#pragma comment(lib, "SPARK_GL_debug.lib")
	#pragma comment(lib, "SPARK_SFML_debug.lib")
#else
	//#pragma comment(lib, "Iphlpapi.lib")
	#pragma comment(lib, "sfml2-audio.lib")
	#pragma comment(lib, "sfml2-graphics.lib")
	#pragma comment(lib, "sfml2-network.lib")
	#pragma comment(lib, "sfml2-system.lib")
	#pragma comment(lib, "sfml2-window.lib")
	#pragma comment(lib, "yamlcpp.lib")
	#pragma comment(lib, "SPARK.lib")
	#pragma comment(lib, "SPARK_GL.lib")
	#pragma comment(lib, "SPARK_SFML.lib")
#endif

#endif