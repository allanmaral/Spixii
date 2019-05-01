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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SPX_PLATFORM_WINDOWS",
			"SPX_BUILD_DLL",
			"_WINDLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "SPX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SPX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SPX_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SPX_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "SPX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SPX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SPX_DIST"
		optimize "On"
