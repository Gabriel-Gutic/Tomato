workspace "TomatoTests"
	architecture "x86_64"
	startproject "TomatoTests"

	configurations
	{
		"Debug",
		"Release",
	}


output_dir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

bin_dir = "%{wks.location}/Build/bin/" ..output_dir.. "/%{prj.name}"
bin_int_dir = "%{wks.location}/Build/bin-int/" ..output_dir.. "/%{prj.name}"

include "../Tomato"

sln = "%{wks.location}/"

project "TomatoTests"
	location "TomatoTests"
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
		"src",
		sln .. "../Tomato/src",
		sln .. "../Tomato/src/Tomato",
		sln .. "../Tomato/dependencies/spdlog/include",
		sln .. "../Tomato/dependencies/ImGui",
	}

	links
	{
		"Tomato",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOMATOTESTS_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "DEBUG"
		defines "TOMATOTESTS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		defines "TOMATOTESTS_RELEASE"
		runtime "Release"
		symbols "on"