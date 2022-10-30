-- premake5.lua
workspace "Engine"
   architecture "x64"
   configurations { "Debug", "Release" }

outputdir = "/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
   location "Engine"
   kind "SharedLib"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   cppdialect "C++17"

   files 
   { 
      "%{prj.name}/src/**.h", 
      "%{prj.name}/src/**.cpp",
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

      defines { "NDEBUG" }
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
      "Engine",
   }

   links
   {
      "Engine",
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
