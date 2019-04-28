#pragma once

#ifdef SPX_PLATFORM_WINDOWS
	#ifdef SPX_BUILD_DLL
		#define SPIXII_API __declspec(dllexport)
	#else
		#define SPIXII_API __declspec(dllimport)
	#endif
#else
	#error Platform not supported
#endif

#define BIT(x) (1 << (x))