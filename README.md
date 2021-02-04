# reVC
[![Build Status](https://img.shields.io/endpoint.svg?url=https%3A%2F%2Factions-badge.atrox.dev%2FGTAmodding%2Fre3%2Fbadge%3Fref%3Dmiami&style=flat)](https://actions-badge.atrox.dev/GTAmodding/re3/goto?ref=miami)
<a href="https://discord.gg/aKYAwCx92H"><img src="https://img.shields.io/badge/discord-join-7289DA.svg?logo=discord&longCache=true&style=flat" /></a>

## Intro

The aim of this project is to reverse GTA Vice City for PC.

## How can I try it?

- reVC requires game assets to work, so you **must** own [a copy of GTA Vice City](https://store.steampowered.com/app/12110/Grand_Theft_Auto_Vice_City/).
- Build reVC or download it from one of the above links (Debug or Release).
- (Optional) If you want to use optional features, copy the files in /gamefiles folder to your game root folder.
- Move reVC.exe to GTA VC directory and run it.

## Latest standalone executables to download 

(Put content of selected archive into gamedir)

- [Windows D3D9 MSS 32bit](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_x86/miami/reVC_Release_win-x86-librw_d3d9-mss.zip)
- [Windows D3D9 64bit](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_amd64/miami/reVC_Release_win-amd64-librw_d3d9-oal.zip)
- [Windows OpenGL 64bit](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_amd64/miami/reVC_Release_win-amd64-librw_gl3_glfw-oal.zip)
- [Linux 64bit](https://nightly.link/GTAmodding/re3/workflows/build-cmake-conan/miami/ubuntu-latest-gl3.zip)
- [MacOS 64bit](https://nightly.link/GTAmodding/re3/workflows/build-cmake-conan/miami/macos-latest-gl3.zip)

## Building from Source  

When using premake, you may want to point GTA_VC_RE_DIR environment variable to GTA Vice City root folder, if you want executable to be moved there via post-build script.

<details><summary>Linux Premake</summary>

For Linux using premake, proceed: [Building on Linux](https://github.com/GTAmodding/re3/wiki/Building-on-Linux)

</details>

<details><summary>Linux Conan</summary>

Obtain source code.
```
git clone https://github.com/GTAmodding/re3.git reVC -b miami
cd reVC
git submodule init
git submodule update --recursive
```
Install python and conan, and then run build.
```
conan export vendor/librw librw/master@
mkdir build
cd build
conan install .. reVC/master@ -if build -o reVC:audio=openal -o librw:platform=gl3 -o librw:gl3_gfxlib=glfw --build missing -s reVC:build_type=RelWithDebInfo -s librw:build_type=RelWithDebInfo
conan build .. -if build -bf build -pf package
```
</details>

<details><summary>FreeBSD</summary>

For FreeBSD using premake, proceed: [Building on FreeBSD](https://github.com/GTAmodding/re3/wiki/Building-on-FreeBSD)

</details>

<details><summary>Windows</summary>

Assuming you have Visual Studio:
- Clone the repo using the argument `--recursive`.
- Run one of the `premake-vsXXXX.cmd` variants on root folder.
- Open the project via Visual Studio  
    
**If you use 64-bit D3D9**: We don't ship 64-bit Dx9 SDK. You need to download it from Microsoft if you don't have it(although it should come pre-installed after some Windows version)  

**If you choose OpenAL on Windows** You must read [Running OpenAL build on Windows](https://github.com/GTAmodding/re3/wiki/Running-OpenAL-build-on-Windows).
</details>

> :information_source: There are various settings in [config.h](https://github.com/GTAmodding/re3/tree/miami/src/core/config.h), you may want to take a look there. i.e. FIX_BUGS define fixes the bugs we've come across.

> :information_source: **Did you notice librw?** reVC uses completely homebrew RenderWare-replacement rendering engine; [librw](https://github.com/aap/librw/). librw comes as submodule of reVC, but you also can use LIBRW enviorenment variable to specify path to your own librw.

## Contributing
Please read the [Coding Style](https://github.com/GTAmodding/re3/blob/miami/CODING_STYLE.md) Document

### Unreversed / incomplete classes  

PS2/Mobile stuff:

	src/core/Pad.cpp
	src/core/main.cpp
	src/core/Frontend_PS2.cpp
	src/core/FrontEndControls.cpp
	src/save/MemoryCard.cpp

