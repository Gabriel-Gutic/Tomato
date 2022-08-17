project "yaml-cpp"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir (bin_dir)
	objdir (bin_int_dir)

	files
	{
		"yaml-cpp/src/**.cpp",
		"yaml-cpp/src/**.h",

		"yaml-cpp/include/**.h",
	}

	includedirs
	{
		"yaml-cpp/include",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

	filter "configurations:Debug"
        defines "YAML_CPP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
        defines "YAML_CPP_RELEASE"
		runtime "Release"
		optimize "on"