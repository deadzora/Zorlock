workspace "Zorlock"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Zorlock/vendor/GLFW/include"
IncludeDir["Glad"] = "Zorlock/vendor/Glad/include"
IncludeDir["ImGui"] = "Zorlock/vendor/imgui"
IncludeDir["glm"] = "Zorlock/vendor/glm"

include "Zorlock/vendor/GLFW"
include "Zorlock/vendor/Glad"
include "Zorlock/vendor/imgui"

project "Zorlock"
	location "Zorlock"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ZLpch.h"
	pchsource "Zorlock/src/ZLpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ZL_PLATFORM_WINDOWS",
			"ZL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "ZL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ZL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZL_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Zorlock/vendor/spdlog/include",
		"Zorlock/src",
		"Zorlock/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Zorlock"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ZL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ZL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ZL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZL_DIST"
		runtime "Release"
		optimize "on"