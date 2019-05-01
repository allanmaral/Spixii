#pragma once

#include "Spixii/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Spixii
{

	class SPIXII_API Log
	{
	public:
		static void Init();

		static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static inline std::shared_ptr<spdlog::logger>& GetApplicationLogger() { return s_ApplicationLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ApplicationLogger;
	};
}

#define SPX_CORE_TRACE(...)    ::Spixii::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SPX_CORE_INFO(...)     ::Spixii::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SPX_CORE_WARN(...)     ::Spixii::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SPX_CORE_ERROR(...)    ::Spixii::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SPX_CORE_CRITICAL(...) ::Spixii::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define SPX_TRACE(...)    ::Spixii::Log::GetApplicationLogger()->trace(__VA_ARGS__)
#define SPX_INFO(...)     ::Spixii::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define SPX_WARN(...)     ::Spixii::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define SPX_ERROR(...)    ::Spixii::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define SPX_CRITICAL(...) ::Spixii::Log::GetApplicationLogger()->critical(__VA_ARGS__)