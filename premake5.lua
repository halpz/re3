workspace "re3"
	configurations { "Release","Debug" }
	location "build"

	files { "src/*.*" }
	files { "src/math/*.*" }
	files { "src/modelinfo/*.*" }
	files { "src/entities/*.*" }
	files { "src/render/*.*" }

	includedirs { "src", "src/modelinfo" }
	includedirs { "src", "src/entities" }
	includedirs { "src", "src/render" }
	includedirs { os.getenv("RWSDK33") }

project "re3"
	kind "SharedLib"
	language "C++"
	targetname "re3"
	targetdir "bin/%{cfg.buildcfg}"
	targetextension ".dll"
	characterset ("MBCS")

	filter "configurations:Debug"
		defines { "DEBUG" }
		flags { "StaticRuntime" }
		symbols "On"
		debugdir "C:/Users/aap/games/gta3_re"
		debugcommand "C:/Users/aap/games/gta3_re/gta3.exe"
		postbuildcommands "copy /y \"$(TargetPath)\" \"C:\\Users\\aap\\games\\gta3_re\\plugins\\re3.dll\""

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		flags { "StaticRuntime" }
		debugdir "C:/Users/aap/games/gta3_re"
		debugcommand "C:/Users/aap/games/gta3_re/gta3.exe"
		postbuildcommands "copy /y \"$(TargetPath)\" \"C:\\Users\\aap\\games\\gta3_re\\plugins\\re3.dll\""
