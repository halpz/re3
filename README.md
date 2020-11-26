# re3
[![Build status](https://ci.appveyor.com/api/projects/status/hyiwgegks122h8jg/branch/master?svg=true)](https://ci.appveyor.com/project/aap/re3/branch/master)
<a href="https://discord.gg/jYpXxTm"><img src="https://img.shields.io/badge/discord-join-7289DA.svg?logo=discord&longCache=true&style=flat" /></a>
| Platform | Debug | Release |
|------------------|-------------|-------------|
| Windows Direct3D9 | [![Download](https://api.bintray.com/packages/gtamodding/re3/Debug_win-x86-librw_d3d9-mss/images/download.svg)](https://bintray.com/gtamodding/re3/Debug_win-x86-librw_d3d9-mss/_latestVersion) | [![Download](https://api.bintray.com/packages/gtamodding/re3/Release_win-x86-librw_d3d9-mss/images/download.svg)](https://bintray.com/gtamodding/re3/Release_win-x86-librw_d3d9-mss/_latestVersion) |
| Windows OpenGL3.3 | [![Download](https://api.bintray.com/packages/gtamodding/re3/Debug_win-x86-librw_gl3_glfw-mss/images/download.svg)](https://bintray.com/gtamodding/re3/Debug_win-x86-librw_gl3_glfw-mss/_latestVersion) | [![Download](https://api.bintray.com/packages/gtamodding/re3/Release_win-x86-librw_gl3_glfw-mss/images/download.svg)](https://bintray.com/gtamodding/re3/Release_win-x86-librw_gl3_glfw-mss/_latestVersion) |

## Intro

The aim of this project is to reverse GTA III for PC by replacing
parts of the game [one by one](https://en.wikipedia.org/wiki/Ship_of_Theseus)
such that we have a working game at all times.

## How can I try it?

- re3 requires game assets to work, so you **must** own [a copy of GTA III](https://store.steampowered.com/app/12100/Grand_Theft_Auto_III/).
- Build re3 or download it from one of the above links (Debug or Release).
- (Optional) If you want to use optional features like Russian language or menu map, copy the files in /gamefiles folder to your game root folder.
- Move re3.exe to GTA 3 directory and run it.

## Preparing the environment for building

You may want to point GTA_III_RE_DIR environment variable to GTA3 root folder if you want executable to be moved there via post-build script.

- For Linux, proceed: [Building on Linux](https://github.com/GTAmodding/re3/wiki/Building-on-Linux)
- For FreeBSD, proceed: [Building on FreeBSD](https://github.com/GTAmodding/re3/wiki/Building-on-FreeBSD) 
- For Windows, assuming you have Visual Studio:
    - Clone the repo using the argument `--recursive`.
    - Run one of the `premake-vsXXXX.cmd` variants on root folder.
    - Open the project via Visual Studio  
    
**If you use 64-bit D3D9**: We don't ship 64-bit Dx9 SDK. You need to download it from Microsoft if you don't have it(although it should come pre-installed after some Windows version)  

There are various settings at the very bottom of [config.h](https://github.com/GTAmodding/re3/tree/master/src/core/config.h), you may want to take a look there. i.e. FIX_BUGS define fixes the bugs we've come across.

> :information_source: **If you choose OpenAL on Windows** You must read [Running OpenAL build on Windows](https://github.com/GTAmodding/re3/wiki/Running-OpenAL-build-on-Windows).

> :information_source: **Did you notice librw?** re3 uses completely homebrew RenderWare-replacement rendering engine; [librw](https://github.com/aap/librw/). librw comes as submodule of re3, but you also can use LIBRW enviorenment variable to specify path to your own librw.

## Contributing
Please read the [Coding Style](https://github.com/GTAmodding/re3/blob/master/CODING_STYLE.md) Document

### Unreversed / incomplete classes (at least the ones we know)
The following classes have only unused or practically unused code left:
```
CMemoryHeap - only on PS2
NameGrid.cpp - only on mobile (a player name grid, either a very early player name code ala GTA1 or a multiplayer leftover)
PedDebug.cpp - only on mobile (debug code)
HandlingMgr.cpp - debug functions from mobile
CVehicle::ProcessBikeWheel - early bike code (only on mobile)
CAutomobile::DebugCode - debug function from mobile
CBoat::DebugCode - debug function from mobile
CBoat::ModifyHandlingValue - debug function from mobile
CBoat::DisplayHandlingData - debug function from mobile
TexturePools - only on PC (slight RW modification that we don't actually need)
```

