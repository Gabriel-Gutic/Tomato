project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir (bin_dir)
	objdir (bin_int_dir)

	files
	{
		"imgui/*.cpp",
		"imgui/*.h",
		"imgui/misc/cpp/*.cpp",
		"imgui/misc/cpp/*.h",
		"imgui/backends/imgui_impl_glfw.h",
		"imgui/backends/imgui_impl_glfw.cpp",
		"imgui/backends/imgui_impl_opengl2.h",
		"imgui/backends/imgui_impl_opengl2.cpp",
		"imgui/backends/imgui_impl_opengl3.h",
		"imgui/backends/imgui_impl_opengl3.cpp",
		"imgui/backends/imgui_impl_opengl3_loader.h",
	}
	
	includedirs
	{
        "imgui",
		"../GLFW/include",
	}

	links
	{
		"GLFW",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

	filter "configurations:Debug"
        defines "IMGUI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
        defines "IMGUI_RELEASE"
		runtime "Release"
		optimize "on"
