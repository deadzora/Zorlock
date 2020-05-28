workspace "Zorlock"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Zorlock/vendor/GLFW/include"
IncludeDir["Glad"] = "Zorlock/vendor/Glad/include"
IncludeDir["ImGui"] = "Zorlock/vendor/imgui"
IncludeDir["glm"] = "Zorlock/vendor/glm"
IncludeDir["stb_image"] = "Zorlock/vendor/stb_image"
IncludeDir["DX11"] = "Zorlock/vendor/DX11/src"
IncludeDir["ZLSL"] = "Zorlock/vendor/ZLSL"
IncludeDir["Assimp"] = "Zorlock/vendor/assimp/include"
IncludeDir["PhysX"] = "Zorlock/vendor/PhysX-4.1/physx/include"

group "Dependencies"
	include "Zorlock/vendor/GLFW"
	include "Zorlock/vendor/Glad"
	include "Zorlock/vendor/imgui"
	include "Zorlock/vendor/assimp"
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
		"%{prj.name}/src/**.md",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/DX11/src/**.h",
		"%{prj.name}/vendor/DX11/src/**.cpp",
		"%{prj.name}/vendor/ZLSL/**.hpp",
		"%{prj.name}/vendor/ZLSL/**.cpp",
		"%{prj.name}/vendor/ZLSL/**.h",
		"%{prj.name}/vendor/PhysX-4.1/physx/include/**.h"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.DX11}",
		"%{IncludeDir.ZLSL}",
		"%{IncludeDir.Assimp}",
		"%{IncludeDir.PhysX}"

	}
	
	libdirs 
	{ 
		"%{prj.name}/vendor/PhysX-4.1/physx/bin"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"Assimp",
		"opengl32.lib",
		"d3d11.lib",
		"d3dcompiler.lib",
		"dxguid.lib",
		"PhysXCooking_static_64.lib",
		"PhysXFoundation_static_64.lib",
		"PhysXCommon_static_64.lib",
		"PhysX_static_64.lib"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.md"
	}

	includedirs
	{
		"Zorlock/vendor/spdlog/include",
		"Zorlock/src",
		"Zorlock/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ZLSL}"
	}

	links
	{
		"Zorlock"
	}

	filter "system:windows"
		systemversion "latest"
		
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
