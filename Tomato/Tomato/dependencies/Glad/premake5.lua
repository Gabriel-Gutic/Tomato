project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir (bin_dir)
	objdir (bin_int_dir)

	files
	{
		"src/**.c",
		"include/**.h",
	}

	includedirs
	{
		"include",
	}

	filter "system:windows"
        systemversion "latest"

        defines
        {
            "GLAD_PLATFORM_WINDOWS",
        }

	filter "configurations:Debug"
		defines "GLAD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GLAD_RELEASE"
		runtime "Release"
		symbols "on"