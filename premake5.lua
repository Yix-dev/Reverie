workspace "Reverie"
architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

IncludeDir = {}

project "ReverieCore"
    location "ReverieCore"
    kind "StaticLib"
    language "C++"
    staticruntime "On"
    cppdialect "C++23"

    targetdir("bin/" ..outputdir .. "/%{prj.name}")
    objdir("bin-int/" ..outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "Reverie/Source/pch.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

    

    includedirs
    {
        "%{prj.name}/Source",
        "%{prj.name}/Vendor/spdlog/include",
        "%{prj.name}/Vendor/DirectX/include"
    }

    filter "system:windows"
        
        staticruntime "On"
        systemversion "latest"
        
        defines
        {
             "HZ_PLATFORM_WINDOWS"   
        }

        links
        {
            "d3d12.lib",
            "dxgi.lib",
            "d3dcompiler.lib",
            "dxguid.lib"
        }
        
        buildoptions
        {
            "/utf-8"
        }

    filter "configurations:Debug"
        defines { "HZ_DEBUG", "HZ_ENABLE_ASSERTS" }
        runtime "Debug" 
        symbols "On"

    filter "configurations:Release"
        defines { "HZ_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "HZ_DIST" }
        runtime "Release"
        optimize "Full"
        
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"  
    staticruntime "off"
    cppdialect "C++23"

    targetdir("bin/" ..outputdir .. "/%{prj.name}")
    objdir("bin-int/" ..outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    } 

    includedirs
    {
        "Reverie/Vendor/spdlog/include",
        "Reverie/Vendor/DirectX/include",
        "Reverie/Source"
    }

    links
    {
        "Reverie"
    }

    filter "system:windows"
        cppdialect "C++23"
        staticruntime "On"
        systemversion "latest"
        

        defines
        {
             "HZ_PLATFORM_WINDOWS"
        }
        buildoptions
        {
            "/utf-8"
        }
        postbuildcommands
        {
        }
    filter "configurations:Debug"
        defines { "HZ_DEBUG" }
        runtime "Debug" 
        symbols "On"

    filter "configurations:Release"
        defines { "HZ_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "HZ_DIST" }
        runtime "Release"
        optimize "Full"