-- Stolen from Cherno's video on premake
-- https://www.youtube.com/watch?v=sULV3aB2qeU

-- Defines the name of the workspace (the Visual Studio .sln file)
workspace "Hessdoku"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	startproject "Hessdoku"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Example project
project "Hessdoku"
	location "Hessdoku"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputDir .. "/%{prj.name}")

	debugdir ("bin/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
	}
	
	includedirs
	{
		"Hessdoku/src",
		"Hessdoku/src/vendor"
	}
	
	filter "system:windows"
		defines "SUDOKU_WINDOWS"
		staticruntime "off"
		runtime "Release"
		systemversion "latest"
		libdirs ("libs")
		links
		{
			"SDL2",
			"SDL2main",
			"SDL2_ttf"
		}
		postbuildcommands ("xcopy ..\\libs\\dlls\\ ..\\bin\\" .. outputDir .. "\\%{prj.name}\\ /s /e /y /i")
		postbuildcommands ("xcopy ..\\dev-assets\\ ..\\bin\\" .. outputDir .. "\\%{prj.name}\\ /s /e /y /i")
		
	filter "system:linux"
		defines "SUDOKU_LINUX"
		staticruntime "off"
		systemversion "latest"
		links
		{
			"SDL2",
			"SDL2main",
			"SDL2_ttf"
		}
		postbuildcommands ("cp ../dev-assets/* ../bin/" .. outputDir .. "/%{prj.name}/ -r")

	filter "configurations:Debug"
		defines
		{
			"SUDOKU_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		optimize "On"