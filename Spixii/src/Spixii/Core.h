#pragma once

#include "Spixii/Base/Type.h"

#ifndef SPIXII_VERSION
#define SPIXII_VERSION 0
#endif

// clang-format off
#ifdef SPX_PLATFORM_WINDOWS
    #ifdef SPX_BUILD_EXE
        #define SPIXII_API
    #else
        #ifdef SPX_BUILD_DLL
            #define SPIXII_API __declspec(dllexport)
        #else
            #define SPIXII_API __declspec(dllimport)
        #endif
    #endif
#else
    #error Platform not supported
#endif
// clang-format on

// MAX 100mb
#define SPX_MAX_BUFFER_SIZE 100 * 1024 * 1024

#ifdef SPX_DEBUG
#define SPX_ENABLE_ASSERTS
#endif

#define BIT(x) (1 << (x))

#ifdef SPX_ENABLE_ASSERTS
#ifdef SPX_PLATFORM_WINDOWS
#define SPX_ASSERT(x, ...)                                                                                  \
    {                                                                                                       \
        if(!(x))                                                                                            \
        {                                                                                                   \
            SPX_ERROR("Assertion Failed: {3} -> {0} \nIn: {1} : {2}", #x, __FILE__, __LINE__, __VA_ARGS__); \
            __debugbreak();                                                                                 \
        }                                                                                                   \
    }
#define SPX_ASSERT_CORE(x, ...)                                                                                  \
    {                                                                                                            \
        if(!(x))                                                                                                 \
        {                                                                                                        \
            SPX_ERROR_CORE("Assertion Failed: {3} -> {0} \nIn: {1} : {2}", #x, __FILE__, __LINE__, __VA_ARGS__); \
            __debugbreak();                                                                                      \
        }                                                                                                        \
    }
#endif  // SPX_PLATFORM_WINDOWS
#else
#define SPX_ASSERT(x, ...)
#define SPX_ASSERT_CORE(x, ...)
#endif