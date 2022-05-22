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


sln = "%{wks.location}/"

include "Tomato"
include "TomatoApp"