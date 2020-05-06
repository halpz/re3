newoption {
	trigger     = "glewdir",
	value       = "PATH",
	description = "Directory of GLEW",
	default     = "glew-2.1.0"
}

newoption {
	trigger     = "glfwdir",
	value       = "PATH",
	description = "Directory of glfw",
	default     = "glfw-3.3.2.bin.WIN32"
}

newoption {
	trigger     = "with-librw",
	description = "Build and use librw from this solution"
}

if(_OPTIONS["with-librw"]) then
	Librw = "librw"
else
	Librw = os.getenv("LIBRW") or "librw"
end

workspace "re3"
	language "C++"
	configurations { "Debug", "Release" }
	location "build"
	symbols "Full"
	staticruntime "off"
	filter { "system:windows" }
		platforms {
			"win-x86-RW33_d3d8-mss",
			"win-x86-librw_d3d9-mss",
			"win-x86-librw_gl3_glfw-mss",
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	filter { "platforms:win*" }
		system "windows"
		
	filter { "platforms:*x86*" }
		architecture "x86"
		
	filter { "platforms:*librw_d3d9*" }
		defines { "RW_D3D9" }
		if(not _OPTIONS["with-librw"]) then
			libdirs { path.join(Librw, "lib/win-x86-d3d9/%{cfg.buildcfg}") }
		end
		
	filter "platforms:*librw_gl3_glfw*"
		defines { "RW_GL3" }
		if(not _OPTIONS["with-librw"]) then
			libdirs { path.join(Librw, "lib/win-x86-gl3/%{cfg.buildcfg}") }
		end
		defines { "GLEW_STATIC" }
		includedirs { path.join(_OPTIONS["glfwdir"], "include") }
		includedirs { path.join(_OPTIONS["glewdir"], "include") }
	filter  {}
	
    pbcommands = { 
       "setlocal EnableDelayedExpansion",
       "set file=$(TargetPath)",
       "FOR %%i IN (\"%file%\") DO (",
       "set filename=%%~ni",
       "set fileextension=%%~xi",
       "set target=!path!!filename!!fileextension!",
       "copy /y \"!file!\" \"!target!\"",
       ")" }
    
    function setpaths (gamepath, exepath, scriptspath)
       scriptspath = scriptspath or ""
       if (gamepath) then
          cmdcopy = { "set \"path=" .. gamepath .. scriptspath .. "\"" }
          table.insert(cmdcopy, pbcommands)
          postbuildcommands (cmdcopy)
          debugdir (gamepath)
          if (exepath) then
             debugcommand (gamepath .. exepath)
             dir, file = exepath:match'(.*/)(.*)'
             debugdir (gamepath .. (dir or ""))
          end
       end
       --targetdir ("bin/%{prj.name}/" .. scriptspath)
    end

if(_OPTIONS["with-librw"]) then
project "librw"
	kind "StaticLib"
	targetname "rw"
	targetdir "lib/%{cfg.platform}/%{cfg.buildcfg}"
	files { path.join(Librw, "src/*.*") }
	files { path.join(Librw, "src/*/*.*") }
	filter "platforms:*RW33*"
		flags { "ExcludeFromBuild" }
	filter  {}
end

local function addSrcFiles( prefix )
	return prefix .. "/*cpp", prefix .. "/*.h", prefix .. "/*.c", prefix .. "/*.ico", prefix .. "/*.aps", prefix .. "/*.rc"
end

project "re3"
	kind "WindowedApp"
	targetname "re3"
	targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}"
	targetextension ".exe"
	characterset ("MBCS")
	linkoptions "/SAFESEH:NO"
	

	files { addSrcFiles("src") }
	files { addSrcFiles("src/animation") }
	files { addSrcFiles("src/audio") }
	--files { addSrcFiles("src/audio/miles") }
	--files { addSrcFiles("src/audio/openal") }
	files { addSrcFiles("src/control") }
	files { addSrcFiles("src/core") }
	files { addSrcFiles("src/entities") }
	files { addSrcFiles("src/math") }
	files { addSrcFiles("src/modelinfo") }
	files { addSrcFiles("src/objects") }
	files { addSrcFiles("src/peds") }
	files { addSrcFiles("src/render") }
	files { addSrcFiles("src/rw") }
	files { addSrcFiles("src/save") }
	files { addSrcFiles("src/skel") }
	files { addSrcFiles("src/skel/win") }
	files { addSrcFiles("src/skel/glfw") }
	files { addSrcFiles("src/text") }
	files { addSrcFiles("src/vehicles") }
	files { addSrcFiles("src/weapons") }
	files { addSrcFiles("src/extras") }
	files { addSrcFiles("eax") }

	includedirs { "src" }
	includedirs { "src/animation" }
	includedirs { "src/audio" }
	includedirs { "src/control" }
	includedirs { "src/core" }
	includedirs { "src/entities" }
	includedirs { "src/math" }
	includedirs { "src/modelinfo" }
	includedirs { "src/objects" }
	includedirs { "src/peds" }
	includedirs { "src/render" }
	includedirs { "src/rw" }
	includedirs { "src/save/" }
	includedirs { "src/skel/" }
	includedirs { "src/skel/win" }
	includedirs { "src/skel/glfw" }
	includedirs { "src/text" }
	includedirs { "src/vehicles" }
	includedirs { "src/weapons" }
	includedirs { "src/extras" }
	includedirs { "eax" }

	includedirs { "milessdk/include" }
	includedirs { "eax" }

	libdirs { "milessdk/lib" }
	
	setpaths("$(GTA_III_RE_DIR)/", "$(TargetFileName)", "")
	
	filter "platforms:*RW33*"
		staticruntime "on"
		includedirs { "rwsdk/include/d3d8" }
		libdirs { "rwsdk/lib/d3d8/release" }
		links { "rwcore", "rpworld", "rpmatfx", "rpskin", "rphanim", "rtbmp", "rtquat", "rtcharse" }
		defines { "RWLIBS" }
		linkoptions "/SECTION:_rwcseg,ER!W /MERGE:_rwcseg=.text"
	
	filter "platforms:*librw*"
		defines { "LIBRW" }
		files { addSrcFiles("src/fakerw") }
		includedirs { "src/fakerw" }
		includedirs { Librw }
		if(_OPTIONS["with-librw"]) then
			libdirs { "lib/%{cfg.platform}/%{cfg.buildcfg}" }
		end
		links { "rw" }

	filter "platforms:*d3d*"
		includedirs { "dxsdk/include" }
		libdirs { "dxsdk/lib" }

	filter "platforms:*d3d9*"
		links { "d3d9" }
		
	filter "platforms:*gl3_glfw*"
		libdirs { path.join(_OPTIONS["glewdir"], "lib/Release/Win32") }
		libdirs { path.join(_OPTIONS["glfwdir"], "lib-" .. string.gsub(_ACTION, "vs", "vc")) }
		links { "opengl32", "glew32s", "glfw3" }


project "reVC"
	kind "WindowedApp"
	targetname "reVC"
	targetdir "bin/%{cfg.platform}/%{cfg.buildcfg}"
	targetextension ".exe"
	characterset ("MBCS")
	linkoptions "/SAFESEH:NO"

	defines { "MIAMI" }

	files { "src/*.*" }
	files { "src/animation/*.*" }
	files { "src/audio/*.*" }
	files { "src/control/*.*" }
	files { "src/core/*.*" }
	files { "src/entities/*.*" }
	files { "src/math/*.*" }
	files { "src/modelinfo/*.*" }
	files { "src/objects/*.*" }
	files { "src/peds/*.*" }
	files { "src/render/*.*" }
	files { "src/rw/*.*" }
	files { "src/save/*.*" }
	files { "src/skel/*.*" }
	files { "src/skel/win/*.*" }
	files { "src/skel/glfw/*.*" }
	files { "src/text/*.*" }
	files { "src/vehicles/*.*" }
	files { "src/weapons/*.*" }
	files { "src/extras/*.*" }
	files { "eax/*.*" }

	includedirs { "src" }
	includedirs { "src/animation" }
	includedirs { "src/audio" }
	includedirs { "src/control" }
	includedirs { "src/core" }
	includedirs { "src/entities" }
	includedirs { "src/math" }
	includedirs { "src/modelinfo" }
	includedirs { "src/objects" }
	includedirs { "src/peds" }
	includedirs { "src/render" }
	includedirs { "src/rw" }
	includedirs { "src/save/" }
	includedirs { "src/skel/" }
	includedirs { "src/skel/win" }
	includedirs { "src/skel/glfw" }
	includedirs { "src/text" }
	includedirs { "src/vehicles" }
	includedirs { "src/weapons" }
	includedirs { "src/extras" }
	includedirs { "eax" }

	includedirs { "milessdk/include" }
	includedirs { "eax" }

	libdirs { "milessdk/lib" }
	
	setpaths("$(GTA_VC_RE_DIR)/", "$(TargetFileName)", "")
	
	filter "platforms:*RW33*"
		staticruntime "on"
		includedirs { "rwsdk/include/d3d8" }
		libdirs { "rwsdk/lib/d3d8/release" }
		links { "rwcore", "rpworld", "rpmatfx", "rpskin", "rphanim", "rtbmp", "rtquat", "rtcharse" }
		defines { "RWLIBS" }
		linkoptions "/SECTION:_rwcseg,ER!W /MERGE:_rwcseg=.text"
	
	filter "platforms:*librw*"
		defines { "LIBRW" }
		files { "src/fakerw/*.*" }
		includedirs { "src/fakerw" }
		includedirs { Librw }
		if(_OPTIONS["with-librw"]) then
			libdirs { "lib/%{cfg.platform}/%{cfg.buildcfg}" }
		end
		links { "rw" }

	filter "platforms:*d3d*"
		includedirs { "dxsdk/include" }
		libdirs { "dxsdk/lib" }

	filter "platforms:*d3d9*"
		links { "d3d9" }
		
	filter "platforms:*gl3_glfw*"
		libdirs { path.join(_OPTIONS["glewdir"], "lib/Release/Win32") }
		libdirs { path.join(_OPTIONS["glfwdir"], "lib-" .. string.gsub(_ACTION, "vs", "vc")) }
		links { "opengl32", "glew32s", "glfw3" }
