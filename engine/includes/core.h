#pragma once
#define PLATFORM_WINDOWS
#ifdef PLATFORM_WINDOWS
	#ifdef BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif // BUILD_DLL
#else
	#error only windows for now
#endif // PLATFORM_WINDOWS
