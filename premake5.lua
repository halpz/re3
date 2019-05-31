workspace "re3"
	configurations { "ReleaseCI", "Release", "ReleaseFH", "Debug" }
	location "build"

	files { "src/*.*" }
	files { "src/skel/*.*" }
	files { "src/math/*.*" }
	files { "src/modelinfo/*.*" }
	files { "src/entities/*.*" }
	files { "src/weapons/*.*" }
	files { "src/render/*.*" }
	files { "src/control/*.*" }
	files { "src/audio/*.*" }

	includedirs { "src" }
	includedirs { "src/modelinfo" }
	includedirs { "src/entities" }
	includedirs { "src/weapons" }
	includedirs { "src/render" }
	includedirs { "src/control" }
	includedirs { "src/audio" }
	includedirs { "rwsdk/include/d3d8" }

project "re3"
	kind "SharedLib"
	language "C++"
	targetname "re3"
	targetdir "bin/%{cfg.buildcfg}"
	targetextension ".dll"
	characterset ("MBCS")

	filter "configurations:Debug"
		defines { "DEBUG" }
		staticruntime "on"
		symbols "On"
		debugdir "C:/Users/aap/games/gta3_re"
		debugcommand "C:/Users/aap/games/gta3_re/gta3.exe"
		postbuildcommands "copy /y \"$(TargetPath)\" \"C:\\Users\\aap\\games\\gta3_re\\plugins\\re3.dll\""

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		staticruntime "on"
		debugdir "C:/Users/aap/games/gta3_re"
		debugcommand "C:/Users/aap/games/gta3_re/gta3.exe"
		postbuildcommands "copy /y \"$(TargetPath)\" \"C:\\Users\\aap\\games\\gta3_re\\plugins\\re3.dll\""
	filter "configurations:ReleaseFH"
		defines { "NDEBUG" }
		symbols "Full"
		optimize "off"
		staticruntime "on"
		debugdir "F:/Rockstar Games/GTAIII"
		debugcommand "F:/Rockstar Games/GTAIII/gta3.exe"
		targetextension ".asi"
		targetdir "F:/Rockstar Games/GTAIII/scripts"
	filter "configurations:ReleaseCI"
		defines { "NDEBUG" }
		optimize "On"
		staticruntime "on"
		
