project "Tomato3D"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir (bin_dir)
	objdir (bin_int_dir)

	pchheader("pch.h")
	pchsource("src/pch.cpp")

	files 
	{
		"src/**.cpp",
		"src/**.h",
	}

	includedirs
	{
		"src",
		sln .. "Tomato/src",
		sln .. "Tomato/src/Tomato",
		sln .. "Tomato/dependencies/spdlog/include",
		sln .. "Tomato/dependencies/entt/src",
		sln .. "Tomato/dependencies/ImGui",
		sln .. "Tomato/dependencies/yaml-cpp/yaml-cpp/include",
	}

	links
	{
		"Tomato",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TOMATO3D_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "DEBUG"
		defines "TOMATO3D_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		defines "TOMATO3D_RELEASE"
		runtime "Release"
		symbols "on"