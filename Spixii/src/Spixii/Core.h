#pragma once

#ifdef SP_PLATFORM_WINDOWS
	#ifdef SP_BUILD_DLL
		#define SPIXII_API __declspec(dllexport)
	#else
		#define SPIXII_API __declspec(dllimport)
	#endif
#else
	#error Platform not supported
#endif