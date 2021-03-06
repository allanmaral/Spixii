#pragma once

#include <functional>
#include <memory>
#include <sstream>

#include <string>

// clang-format off
#ifdef SPX_PLATFORM_WINDOWS
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#endif
// clang-format on