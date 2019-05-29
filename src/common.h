#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#pragma warning(disable: 4244)	// int to float
#pragma warning(disable: 4800)	// int to bool
#pragma warning(disable: 4305)	// double to float
#pragma warning(disable: 4838)  // narrowing conversion
#pragma warning(disable: 4996)  // POSIX names

#include <stdint.h>
#include <math.h>
#include <assert.h>
#include <new>

#include <rwcore.h>
#include <rpworld.h>

#define rwVENDORID_ROCKSTAR 0x0253F2

typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uintptr_t uintptr;

#define nil NULL

#include "config.h"

#define ALIGNPTR(p) (void*)((((uintptr)(void*)p) + sizeof(void*)-1) & ~(sizeof(void*)-1))

// little hack
extern void **rwengine;
#define RwEngineInstance (*rwengine)

// TODO
struct RsInputDevice
{
	int inputDeviceType;
	int used;
	void *inputEventHandler;
};

struct RsGlobalType
{
	const char *appName;
	int width;
	int height;
	int maximumWidth;
	int maximumHeight;
	int maxFPS;
	int quit;
	void *ps;
	RsInputDevice keyboard;
	RsInputDevice mouse;
	RsInputDevice pad;
};
extern RsGlobalType &RsGlobal;

#define SCREENW (RsGlobal.maximumWidth)
#define SCREENH (RsGlobal.maximumHeight)

char *GetUserDirectory(void);

struct GlobalScene
{
	RpWorld *world;
	RwCamera *camera;
};
extern GlobalScene &Scene;

#include "math/Vector.h"
#include "math/Vector2D.h"
#include "math/Matrix.h"
#include "math/Rect.h"

class CRGBA
{
public:
	uint8 r, g, b, a;
	CRGBA(void) { }
	CRGBA(uint8 r, uint8 g, uint8 b, uint8 a) : r(r), g(g), b(b), a(a) { }
};

inline float
clamp(float v, float min, float max){ return v<min ? min : v>max ? max : v; }
inline float
sq(float x) { return x*x; }
#define PI M_PI
#define DEGTORAD(d) (d/180.0f*PI)

int myrand(void);
void mysrand(unsigned int seed);

#define debug printf

//#define min(a, b) ((a) < (b) ? (a) : (b))
//#define max(a, b) ((a) > (b) ? (a) : (b))
