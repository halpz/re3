# reVC
[![Build status](https://ci.appveyor.com/api/projects/status/hyiwgegks122h8jg/branch/miami?svg=true)](https://ci.appveyor.com/project/aap/re3/branch/miami)
<a href="https://discord.gg/jYpXxTm"><img src="https://img.shields.io/badge/discord-join-7289DA.svg?logo=discord&longCache=true&style=flat" /></a>
| Platform | Debug | Release |
|------------------|-------------|-------------|
| Windows Direct3D9 | [![Download](https://api.bintray.com/packages/gtamodding/revc/Debug_win-x86-librw_d3d9-mss/images/download.svg)](https://bintray.com/gtamodding/revc/Debug_win-x86-librw_d3d9-mss/_latestVersion) | [![Download](https://api.bintray.com/packages/gtamodding/revc/Release_win-x86-librw_d3d9-mss/images/download.svg)](https://bintray.com/gtamodding/revc/Release_win-x86-librw_d3d9-mss/_latestVersion) |
| Windows OpenGL3.3 | [![Download](https://api.bintray.com/packages/gtamodding/revc/Debug_win-x86-librw_gl3_glfw-mss/images/download.svg)](https://bintray.com/gtamodding/revc/Debug_win-x86-librw_gl3_glfw-mss/_latestVersion) | [![Download](https://api.bintray.com/packages/gtamodding/revc/Release_win-x86-librw_gl3_glfw-mss/images/download.svg)](https://bintray.com/gtamodding/revc/Release_win-x86-librw_gl3_glfw-mss/_latestVersion) |

## Intro

The aim of this project is to reverse GTA Vice City for PC.

## How can I try it?

- reVC requires game assets to work, so you **must** own [a copy of GTA Vice City](https://store.steampowered.com/app/12110/Grand_Theft_Auto_Vice_City/).
- Build reVC or download it from one of the above links (Debug or Release).
- (Optional) If you want to use optional features, copy the files in /gamefiles folder to your game root folder.
- Move reVC.exe to GTA VC directory and run it.

## Preparing the environment for building

You may want to point GTA_VC_RE_DIR environment variable to GTA VC root folder if you want executable to be moved there via post-build script.

- For Linux, proceed: [Building on Linux](https://github.com/GTAmodding/re3/wiki/Building-on-Linux)
- For FreeBSD, proceed: [Building on FreeBSD](https://github.com/GTAmodding/re3/wiki/Building-on-FreeBSD) 
- For Windows, assuming you have Visual Studio:
    - Clone the repo using the argument `--recursive`.
    - Run one of the `premake-vsXXXX.cmd` variants on root folder.
    - Open the project via Visual Studio  
    
**If you use 64-bit D3D9**: We don't ship 64-bit Dx9 SDK. You need to download it from Microsoft if you don't have it(although it should come pre-installed after some Windows version)  

There are various settings at the very bottom of [config.h](https://github.com/GTAmodding/re3/tree/miami/src/core/config.h), you may want to take a look there. i.e. FIX_BUGS define fixes the bugs we've come across.

> :information_source: **If you choose OpenAL on Windows** You must read [Running OpenAL build on Windows](https://github.com/GTAmodding/re3/wiki/Running-OpenAL-build-on-Windows).

> :information_source: **Did you notice librw?** reVC uses completely homebrew RenderWare-replacement rendering engine; [librw](https://github.com/aap/librw/). librw comes as submodule of reVC, but you also can use LIBRW enviorenment variable to specify path to your own librw.

## Contributing
Please read the [Coding Style](https://github.com/GTAmodding/re3/blob/master/CODING_STYLE.md) Document

### Unreversed / incomplete classes (at least the ones we know)
See [VC todo list](https://github.com/GTAmodding/re3/wiki/VC-todo)

