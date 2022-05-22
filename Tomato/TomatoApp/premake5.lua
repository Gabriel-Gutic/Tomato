project "TomatoApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir (bin_dir)
	objdir (bin_int_dir)

	files 
	{
		"src/**.cpp",
		"src/**.h",
	}

	includedirs
	{
		"src",
		sln .. "Tomato/src",
		sln .. "Tomato/dependencies/spdlog/include",
	}

	links
	{
		"Tomato",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOMATOAPP_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "DEBUG"
		defines "TOMATOAPP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		defines "TOMATOAPP_RELEASE"
		runtime "Release"
		symbols "on"