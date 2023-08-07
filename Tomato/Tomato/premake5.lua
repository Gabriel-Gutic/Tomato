
project "Tomato"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir (bin_dir)
	objdir (bin_int_dir)

	-- pchheader("pchTomato.h")
	-- pchsource("src/pchTomato.cpp")

	files 
	{
		"src/**.cpp",
		"src/**.h",
	}

	includedirs
	{
		"src",
		"src/Tomato",
	}

	links 
	{
		
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOMATO_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "DEBUG"
		defines "TOMATO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		defines "TOMATO_RELEASE"
		runtime "Release"
		symbols "on"