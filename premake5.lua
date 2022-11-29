workspace "ForgeEngine"

   architecture "x64"
   configurations
   {
		  "Debug",
		  "Release",
		  "Dist"
   }

outputdir ="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir ={}
IncludeDir["GLFW"] = "dependencies/Libraries/GLFW/include"
IncludeDir["GLAD"] = "dependencies/Libraries/GLAD/include"
IncludeDir["UI"]  =  "vendor/UI/central"
IncludeDir["img_loader"]  =  "engine/helpers/img_loader"
IncludeDir["ecs"]  =  "engine/helpers/ecs"

include "dependencies/Libraries/GLFW"
include "dependencies/Libraries/GLAD"
include "vendor/UI/central"


project "engine"
      
        location "engine"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir("binaries/" .. outputdir .. "/%{prj.name}")
		objdir("obj/" .. outputdir .. "/%{prj.name}")

		pchheader "frpch.h"
		pchsource "engine/source/frpch.cpp"

		 files
         {
          "%{prj.name}/source/**.h",
          "%{prj.name}/source/**.cpp",
		  "%{prj.name}/helpers/img_loader/**.h",
		  "%{prj.name}/helpers/img_loader/**.cpp"
         }

		 defines{
			  "_CRT_SECURE_NO_WARNINGS"
		 }

		 includedirs
		 {
			   "%{prj.name}/source",
			  "vendor/thirdparty/LOG/include",
			  "dependencies/Libraries/GLM",
			  "%{IncludeDir.GLFW}",
			   "%{IncludeDir.GLAD}",
			   "%{IncludeDir.UI}",
			    "%{IncludeDir.img_loader}",
				"%{IncludeDir.ecs}"
			  
		 }

		 links
		 {
		      "GLFW",
			  "GLAD",
			  "ImGui",
			  "opengl32.lib"
		 }


		 filter "system:windows"
			
			staticruntime "on"
			systemversion "latest"

			defines
			{
			   "FR_PLATFORM_WINDOWS",
			   "FR_BUILD_DLL",
			   "GLFW_INCLUDE_NONE"
			}

			filter "configurations:Debug"
					 defines "FR_DEBUG"
					 buildoptions "/MDd"
					 symbols "on"

			filter "configurations:Release"
					defines "FR_RELEASE"
					buildoptions "/MD"
					optimize "on"



project "Anvil"

	location "editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")       

	files
    {
    "%{prj.name}/Anvil/source/**.h",
    "%{prj.name}/Anvil/source/**.cpp",
    }

	includedirs
	{
		"vendor/thirdparty/LOG/include",
		"dependencies/Libraries/GLM",
		"vendor/UI/central",
		"engine/source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ecs}"
			 
	}

	links
	{
		"engine",
		"GLFW",
		"GLAD"
			
	}

	filter "system:windows"
			
	staticruntime "on"
	systemversion "latest"

	defines
	{
		"FR_PLATFORM_WINDOWS"
	}

		filter "configurations:Debug"
				defines "FR_DEBUG"
			    buildoptions "/MDd"
				symbols "on"

	filter "configurations:Release"
			defines "FR_RELEASE"
					
			optimize "on"




			

 project "ForgeApp"

		 location "runtime"
		 kind "ConsoleApp"
		 language "C++"
		 cppdialect "C++17"
		 staticruntime "on"

		 targetdir ("binaries/" .. outputdir .. "/%{prj.name}")
		 objdir ("obj/" .. outputdir .. "/%{prj.name}")       

		  files
         {
          "%{prj.name}/source/**.h",
          "%{prj.name}/source/**.cpp",
         }

		 includedirs
		 {
		      "vendor/thirdparty/LOG/include",
			   "dependencies/Libraries/GLM",
			  "vendor/UI/central",
			  "engine/source",
			  "%{IncludeDir.GLFW}",
			  "%{IncludeDir.GLAD}",
			  "%{IncludeDir.ecs}"
			 
		 }

		 links
		 {
			 "engine",
			 "GLFW",
			  "GLAD"
			
		 }

		 filter "system:windows"
			
			staticruntime "on"
			systemversion "latest"

			defines
			{
			   "FR_PLATFORM_WINDOWS"
			}

			 filter "configurations:Debug"
					 defines "FR_DEBUG"
			         buildoptions "/MDd"
					 symbols "on"

			filter "configurations:Release"
					defines "FR_RELEASE"
					
					optimize "on"

		

			
