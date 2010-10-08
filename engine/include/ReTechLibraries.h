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