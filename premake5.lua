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
    pchsource "ReverieCore/Source/pch.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "app.manifest"
    }

    

    includedirs
    {
        "%{prj.name}/Source",
        "%{prj.name}/Vendor/spdlog/include",
        "%{prj.name}/Vendor/DirectX/include",
        "%{prj.name}/Vendor/miniaudio"
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
        defines { "REVERIE_DEBUG", "REVERIE_ENABLE_ASSERTS" }
        runtime "Debug" 
        symbols "On"

    filter "configurations:Release"
        defines { "REVERIE_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "REVERIE_DIST" }
        runtime "Release"
        optimize "Full"
        
project "Sandbox"
    location "Sandbox"
    kind "WindowedApp"
    language "C++"  
    staticruntime "off"
    cppdialect "C++23"

    targetdir("bin/" ..outputdir .. "/%{prj.name}")
    objdir("bin-int/" ..outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
        "app.manifest"
    } 

    includedirs
    {
        "ReverieCore/Vendor/spdlog/include",
        "ReverieCore/Vendor/DirectX/include",
        "ReverieCore/Vendor/miniaudio",
        "ReverieCore/Source"
    }

    links
    {
        "ReverieCore"
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
        defines { "REVERIE_DEBUG" }
        runtime "Debug" 
        symbols "On"

    filter "configurations:Release"
        defines { "REVERIE_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "REVERIE_DIST" }
        runtime "Release"
        optimize "Full"