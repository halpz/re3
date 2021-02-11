[![Build Status](https://img.shields.io/endpoint.svg?url=https%3A%2F%2Factions-badge.atrox.dev%2FGTAmodding%2Fre3%2Fbadge%3Fref%3Dmiami&style=flat)](https://actions-badge.atrox.dev/GTAmodding/re3/goto?ref=miami)
<a href="https://discord.gg/aKYAwCx92H"><img src="https://img.shields.io/badge/discord-join-7289DA.svg?logo=discord&longCache=true&style=flat" /></a>

## Intro

In this repository you'll find the fully reversed source code for GTA III ([master](tree/master) branch) and GTA VC ([miami](tree/miami) branch).

It has been tested and works on Windows, Linux and FreeBSD, on x86, amd64, arm and arm64.\
Rendering is handled either by original RenderWare (D3D8)
or the reimplementation [librw](https://github.com/aap/librw) (D3D9, OpenGL 2.1 or above, OpenGL ES 2.0 or above).\
Audio is done with MSS (using dlls from original GTA) or OpenAL.

We cannot build for PS2 or Xbox yet. If you're interested in doing so, get in touch with us.

## How can I try it?

- reVC requires game assets to work, so you **must** own [a copy of GTA Vice City](https://store.steampowered.com/app/12110/Grand_Theft_Auto_Vice_City/).
- Build reVC or download the latest nightly build:
  - [Windows D3D9 MSS 32bit](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_x86/miami/reVC_Release_win-x86-librw_d3d9-mss.zip)
  - [Windows D3D9 64bit](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_amd64/miami/reVC_Release_win-amd64-librw_d3d9-oal.zip)
  - [Windows OpenGL 64bit](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_amd64/miami/reVC_Release_win-amd64-librw_gl3_glfw-oal.zip)
  - [Linux 64bit](https://nightly.link/GTAmodding/re3/workflows/build-cmake-conan/miami/ubuntu-latest-gl3.zip)
  - [MacOS 64bit](https://nightly.link/GTAmodding/re3/workflows/build-cmake-conan/miami/macos-latest-gl3.zip)
- Copy the files from the `gamefiles` directory to your game root directory. (This is not strictly necessary but very much recommended)
- Move reVC executable to GTA VC directory and run it.

## Screenshots

![screen_ 1613086852](https://user-images.githubusercontent.com/1521437/107714115-fa18f580-6ccc-11eb-9de5-eb4cd04865d3.png)
![screen_ 1613086989](https://user-images.githubusercontent.com/1521437/107714103-f38a7e00-6ccc-11eb-88a3-c8c2033c51d6.png)
![screen_ 1613087193](https://user-images.githubusercontent.com/1521437/107714106-f4bbab00-6ccc-11eb-96a9-13821d9b9684.png)
![screen_ 1613087332](https://user-images.githubusercontent.com/1521437/107714111-f84f3200-6ccc-11eb-902e-d757481d579a.png)

## Improvements

We have implemented a number of changes and improvements to the original game.
They can be configured in `core/config.h`.
Some of them can be toggled at runtime, some cannot.

* Fixed a lot of smaller and bigger bugs
* User files (saves and settings) stored in GTA root directory
* Settings stored in reVC.ini file instead of gta_vc.set
* Debug menu to do and change various things (Ctrl-M to open)
* Debug camera (Ctrl-B to toggle)
* Rotatable camera
* Xinput controller support (Windows)
* No loading screens between islands ("map memory usage" in menu)
* Rendering
  * Widescreen support (properly scaled HUD, Menu and FOV)
  * PS2 MatFX (vehicle reflections)
  * PS2 alpha test (better rendering of transparency)
  * Xbox vehicle rendering
  * Xbox world lightmap rendering (needs Xbox map)
  * Xbox ped rim light
  * Xbox screen rain droplets
  * More customizable colourfilter
* Menu
  * More options
  * Controller configuration menu
  * ...
* Can load DFFs and TXDs from other platforms, possibly with a performance penalty
* ...

## To-Do

The following things would be nice to have/do:

* Fix physics for high FPS
* [PS2 port](https://github.com/GTAmodding/re3/wiki/PS2-port)
* Xbox port (not quite as important)
* reverse remaining unused/debug functions
* compare Codewarrior build with original binary for more accurate code (very tedious)

## Modding

Asset modifications (models, texture, handling, script, ...) should work the same way as with original GTA for the most part.

Mods that make changes to the code (dll/asi, CLEO, limit adjusters) will *not* work.
Some things these mods do are already implemented in re3 (much of SkyGFX, GInput, SilentPatch, Widescreen fix),
others can easily be achieved (increasing limis, see `config.h`),
others will simply have to be rewritten and integrated into the code directly.
Sorry for the inconvenience.

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
We have a [Coding Style](https://github.com/GTAmodding/re3/blob/master/CODING_STYLE.md) document that isn't followed or enforced very well.

Do not use features from C++11 or later.


## License

We don't feel like we're in a position to give this code a license.
If we were, it would be MIT licensed.
