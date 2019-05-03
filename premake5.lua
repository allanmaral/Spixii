workspace "Spixii"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["EASTL"] = "Spixii/ThirdParty/EASTL/include"
IncludeDir["spdlog"] = "Spixii/ThirdParty/spdlog/include"

include "Spixii/ThirdParty/EASTL"

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
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.EASTL}"
    }

    links
    {
        "EASTL"
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
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.EASTL}",
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
