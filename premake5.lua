workspace "Spixii"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Spixii"
	location "Spixii"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/obj/" .. outputdir .. "/%{prj.name}")

	pchheader "spxpch.h"
	pchsource "Spixii/src/spxpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/ThirdParty/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SPX_PLATFORM_WINDOWS",
			"SPX_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "SPX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SPX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SPX_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Spixii/ThirdParty/spdlog/include",
		"Spixii/src"
	}

	links
	{
		"Spixii"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SPX_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "SPX_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SPX_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "SPX_DIST"
		runtime "Release"
		optimize "On"
