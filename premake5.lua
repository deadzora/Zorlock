workspace "Zorlock"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Zorlock"
	location "Zorlock"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZL_PLATFORM_WINDOWS",
			"ZL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "ZL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ZL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ZL_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Zorlock/Vendor/spdlog/include",
		"Zorlock/src"
	}

	links
	{
		"Zorlock"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ZL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ZL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ZL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ZL_DIST"
		optimize "On" 