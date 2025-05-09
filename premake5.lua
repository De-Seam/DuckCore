
--- DuckCore project

project "DuckCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    cdialect "C17"
    targetdir "%{wks.location}/Build/Out/%{prj.name}/%{plat}_%{cfg.buildcfg}/"
    objdir "%{wks.location}/Build/Int/%{prj.name}/%{plat}_%{cfg.buildcfg}/"
    files { "DuckCore/**.h", "DuckCore/**.cpp" }
    includedirs { path.getabsolute("./") } -- Include the workspace/solution directory
	location "DuckCore"
	flags { "MultiProcessorCompile" }
	warnings "Extra"

	filter "system:windows"
           buildoptions { "/MP", "/W4" }  -- Enable multi-processor and set warning level to 4

    filter "system:linux"
        targetdir "Build/Out/%{prj.name}/linux_%{cfg.buildcfg}/"
        objdir "Build/Int/%{prj.name}/linux_%{cfg.buildcfg}/"
        defines { "SDL_VIDEO_DRIVER_X11" }  -- Define the appropriate driver for Linux
        links { "SDL2" }  -- Link against the SDL2 library
        includedirs { "/usr/include/SDL2" }  -- Include the SDL2 headers

    filter "configurations:Debug"
        defines { "_DEBUG" }
		symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
		optimize "On"
			
	filter "configurations:Ship"
        defines { "_SHIP" }
		optimize "On"
			
--- External project

project "External"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    cdialect "C17"
    targetdir "%{wks.location}/Build/Out/%{prj.name}/%{plat}_%{cfg.buildcfg}/"
    objdir "%{wks.location}/Build/Int/%{prj.name}/%{plat}_%{cfg.buildcfg}/"
    files { "External/**.h", "External/**.cpp" }
    includedirs { path.getabsolute("./") } -- Include the workspace/solution directory
	location "DuckCore"
	flags { "MultiProcessorCompile" }
	warnings "Extra"

	filter "system:windows"
           buildoptions { "/MP", "/W4" }  -- Enable multi-processor and set warning level to 4

    filter "system:linux"
        targetdir "Build/Out/%{prj.name}/linux_%{cfg.buildcfg}/"
        objdir "Build/Int/%{prj.name}/linux_%{cfg.buildcfg}/"
        defines { "SDL_VIDEO_DRIVER_X11" }  -- Define the appropriate driver for Linux
        links { "SDL2" }  -- Link against the SDL2 library
        includedirs { "/usr/include/SDL2" }  -- Include the SDL2 headers

    filter "configurations:Debug"
        defines { "_DEBUG" }
		symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
		optimize "On"
			
	filter "configurations:Ship"
        defines { "_SHIP" }
		optimize "On"