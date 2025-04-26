
--- DuckCore project

project "DuckCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    cdialect "C17"
    targetdir "Build/Out/%{prj.name}/%{cfg.buildcfg}/"
    objdir "Build/Int/%{prj.name}/%{cfg.buildcfg}/"
    location "DuckCore"
    files { "DuckCore/**.h", "DuckCore/**.cpp" }
    includedirs { path.getabsolute("./"), path.getabsolute("./") .. "/External/" }

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
    targetdir "Build/Out/%{prj.name}/%{cfg.buildcfg}/"
    objdir "Build/Int/%{prj.name}/%{cfg.buildcfg}/"
    location "External"
    files { "External/**.h", "External/**.cpp" }
    includedirs { path.getabsolute("./") } -- Include the workspace/solution directory
	links { }

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