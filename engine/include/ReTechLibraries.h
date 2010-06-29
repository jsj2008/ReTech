#ifndef __rtLibraries_H__
#define __rtLibraries_H__

#ifdef _DEBUG
	#pragma comment(lib, "Iphlpapi.lib")
	#pragma comment(lib, "sfml-audio-s-d.lib")
	#pragma comment(lib, "sfml-graphics-s-d.lib")
	#pragma comment(lib, "sfml-network-s-d.lib")
	#pragma comment(lib, "sfml-system-s-d.lib")
	#pragma comment(lib, "sfml-window-s-d.lib")
	#pragma comment(lib, "yamlcppd.lib")
#else
	#pragma comment(lib, "Iphlpapi.lib")
	#pragma comment(lib, "sfml-audio-s.lib")
	#pragma comment(lib, "sfml-graphics-s.lib")
	#pragma comment(lib, "sfml-network-s.lib")
	#pragma comment(lib, "sfml-system-s.lib")
	#pragma comment(lib, "sfml-window-s.lib")
	#pragma comment(lib, "yamlcpp.lib")
#endif

#endif