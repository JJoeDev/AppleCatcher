workspace "SimpleGame"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "build"

    filter "configurations:Debug"
        defines { "DEBUG" }
        optimize "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "SimpleGame"
    kind "ConsoleApp"
    language "C++"
    targetdir("bin/%{cfg.buildcfg}")
    objdir("obj/%{cfg.buildcfg}")

    files{
        "src/**.cpp",
        "src/**.h"
    }

    includedirs{
        "src/",
        "E2DE/include/**.h",
    }

    links{
        "E2DE",
        "SDL2",
        "SDL2main"
    }

    libdirs{
        "E2DE/lib"
    }