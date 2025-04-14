
--- DuckCore project

project "DuckCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    cdialect "C17"
    targetdir "Build/Out/%{prj.name}/%{plat}_%{cfg.buildcfg}/"
    objdir "Build/Int/%{prj.name}/%{plat}_%{cfg.buildcfg}/"
    location "DuckCore"
    files { "DuckCore/**.h", "DuckCore/**.cpp" }
    includedirs { path.getabsolute("./") } -- Include the workspace/solution directory

    filter "system:linux"
        targetdir "Build/Out/%{prj.name}/linux_%{cfg.buildcfg}/"
        objdir "Build/Int/%{prj.name}/linux_%{cfg.buildcfg}/"
        defines { "SDL_VIDEO_DRIVER_X11" }  -- Define the appropriate driver for Linux
        links { "SDL2" }  -- Link against the SDL2 library
        includedirs { "/usr/include/SDL2" }  -- Include the SDL2 headers

    filter "configurations:Debug"
        defines { "DEBUG" }
		warnings "Extra"
        symbols "On"
		flags { "MultiProcessorCompile" }
        filter "system:windows"
            buildoptions { "/MP", "/W4" }  -- Enable multi-processor and set warning level to 4

    filter "configurations:Release"
        defines { "NDEBUG" }
		warnings "Extra"
        optimize "On"
		flags { "MultiProcessorCompile" }
        filter "system:windows"
            buildoptions { "/MP", "/W4" }  -- Enable multi-processor and set warning level to 4
			
--- External project

project "External"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    cdialect "C17"
    targetdir "Build/Out/%{prj.name}/%{plat}_%{cfg.buildcfg}/"
    objdir "Build/Int/%{prj.name}/%{plat}_%{cfg.buildcfg}/"
    location "External"
    files { "External/**.h", "External/**.cpp" }
    includedirs { path.getabsolute("./") } -- Include the workspace/solution directory
	
	defines { "SDL_VIDEO_DRIVER_X11" }  -- Define the appropriate driver for Linux
    links { "SDL2" }  -- Link against the SDL2 library

    filter "system:linux"
        targetdir "Build/Out/%{prj.name}/linux_%{cfg.buildcfg}/"
        objdir "Build/Int/%{prj.name}/linux_%{cfg.buildcfg}/"
        includedirs { "/usr/include/SDL2" }  -- Include the SDL2 headers

    filter "configurations:Debug"
        defines { "DEBUG" }
		warnings "Extra"
        symbols "On"
		flags { "MultiProcessorCompile" }
        filter "system:windows"
            buildoptions { "/MP", "/W4" }  -- Enable multi-processor and set warning level to 4

    filter "configurations:Release"
        defines { "NDEBUG" }
		warnings "Extra"
        optimize "On"
		flags { "MultiProcessorCompile" }
        filter "system:windows"
            buildoptions { "/MP", "/W4" }  -- Enable multi-processor and set warning level to 4