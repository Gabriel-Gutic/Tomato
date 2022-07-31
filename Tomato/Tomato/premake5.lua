dependencies = {}
dependencies["GLFW"] = "dependencies/GLFW/include"
dependencies["Glad"] = "dependencies/Glad/include"
dependencies["ImGui"] = "dependencies/ImGui"

group "Dependencies"
	include "dependencies/GLFW"
	include "dependencies/Glad"
	include "dependencies/ImGui"
group ""

project "Tomato"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir (bin_dir)
	objdir (bin_int_dir)

	pchheader("pchTomato.h")
	pchsource("src/pchTomato.cpp")

	files 
	{
		"src/**.cpp",
		"src/**.h",
	}

	includedirs
	{
		"src",
		"src/Tomato",
		"dependencies/stb_image",
		"dependencies/spdlog/include",
		dependencies["GLFW"],
		dependencies["Glad"],
		dependencies["ImGui"],
		dependencies["ImGui"] .. "/imgui",
	}

	links 
	{
		"GLFW",
		"Glad",
		"ImGui",
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