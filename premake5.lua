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
IncludeDir["assimp"] = "ZorlockDX11/includes/assimp"

group "Dependencies"
	include "Zorlock/vendor/GLFW"
	include "Zorlock/vendor/Glad"
	include "Zorlock/vendor/imgui"
group ""

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
	
project "ZorlockDX11"
	location "ZorlockDX11"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/includes/noise/**.h",
		"%{prj.name}/includes/noise/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.assimp}",
		"%{prj.name}/includes/imgui"

	}
	
	libdirs { "%{prj.name}/vendor/assimp" }
	
	links 
	{ 
		"d3d11.lib",
		"d3dcompiler.lib",
		"assimp-vc140-mt.lib",
		"dxguid.lib",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ZL_PLATFORM_WINDOWS",
			"ZL_BUILD_DLL",
			"NOMINMAX"
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