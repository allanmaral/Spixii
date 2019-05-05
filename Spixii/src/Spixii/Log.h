#pragma once

#include "Spixii/Core.h"
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#define SPX_LOG_ENABLED

namespace Spixii
{
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_coreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetApplicationLogger() { return s_applicationLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_applicationLogger;
    };

#ifdef SPX_BUILD_DLL
    extern Log g_logger;
#endif

}  // namespace Spixii

// clang-format off
#ifdef SPX_LOG_ENABLED
// Core log macros
#define SPX_TRACE_CORE(...) ::Spixii::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SPX_INFO_CORE(...)  ::Spixii::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SPX_WARN_CORE(...)  ::Spixii::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SPX_ERROR_CORE(...) ::Spixii::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SPX_FATAL_CORE(...) ::Spixii::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define SPX_TRACE(...)      ::Spixii::Log::GetApplicationLogger()->trace(__VA_ARGS__)
#define SPX_INFO(...)       ::Spixii::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define SPX_WARN(...)       ::Spixii::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define SPX_ERROR(...)      ::Spixii::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define SPX_FATAL(...)      ::Spixii::Log::GetApplicationLogger()->fatal(__VA_ARGS__)
#else
#define SPX_TRACE_CORE(...)
#define SPX_INFO_CORE(...)
#define SPX_WARN_CORE(...)
#define SPX_ERROR_CORE(...)
#define SPX_FATAL_CORE(...)
#define SPX_TRACE(...)
#define SPX_INFO(...)
#define SPX_WARN(...)
#define SPX_ERROR(...)
#define SPX_FATAL(...)
#endif
// clang-format on