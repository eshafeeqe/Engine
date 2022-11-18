-- premake5.lua
workspace "Engine"
   architecture "x64"
   configurations { "Debug", "Release" }
   toolset ("clang")

outputdir = "/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"

include "Engine/vendor/GLFW"

project "Engine"
   location "Engine"
   kind "SharedLib"
   language "C++"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   pchheader "egpch.h"

   cppdialect "C++17"

   files 
   { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp",
   }

   includedirs
   {
      "%{prj.name}",
      "%{prj.name}/src",
      "%{prj.name}/vendor/spdlog/include",
      "%{IncludeDir.GLFW}" 
   }

   links
   {
      "GLFW",
      "pthread", "dl"
   }

   filter "configurations:Debug"
      defines { "EG_DEBUG"}
      symbols "On"

   filter "configurations:Release"
      defines { "EG_RELEASE" }
      optimize "On"

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   cppdialect "C++17"
   
   files 
   { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp",
   }

   includedirs
   {
      "Engine/src",
      "Engine/vendor/spdlog/include", 
   }

   links
   {
      "Engine",
   }

   filter "configurations:Debug"
      defines { "EG_DEBUG"}
      symbols "On"

   filter "configurations:Release"
      defines { "EG_RELEASE" }
      optimize "On"
