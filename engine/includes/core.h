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

//#ifdef EN_ENABLE_ASSERTS
	#define EN_ASSERT(x, ...) { if(!(x)) { EN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EN_CORE_ASSERT(x, ...) { if(!(x)) { EN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
/*#else
	#define EN_ASSERT(x, ...)
	#define EN_CORE_ASSERT(x, ...)
#endif*/

#define BIT(x) (1 << x)
#include <enpch.hpp>