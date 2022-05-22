workspace "Tomato"
	architecture "x86_64"
	startproject "TomatoApp"

	configurations
	{
		"Debug",
		"Release",
	}

output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

bin_dir = "%{wks.location}/Build/bin/" ..output_dir.. "/%{prj.name}"
bin_int_dir = "%{wks.location}/Build/bin-int/" ..output_dir.. "/%{prj.name}"

project "Tomato"
	location "Tomato"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir (bin_dir)
	objdir (bin_int_dir)

	pchheader("pchTomato.h")
	pchsource("%{prj.name}/src/pchTomato.cpp")

	files 
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/Tomato",
		"%{prj.name}/dependencies/spdlog/include",
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

project "TomatoApp"
	location "TomatoApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir (bin_dir)
	objdir (bin_int_dir)

	files 
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
	}

	includedirs
	{
		"%{prj.name}/src",
		"Tomato/src",
		"Tomato/dependencies/spdlog/include",
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