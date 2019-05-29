#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#pragma warning(disable: 4244)	// int to float
#pragma warning(disable: 4800)	// int to bool
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

typedef char                            Int8;
typedef unsigned char                   UInt8;
typedef signed char                     SInt8;
typedef short                           Int16;
typedef unsigned short                  UInt16;
typedef signed short                    SInt16;
typedef int                             Int32;
typedef unsigned int                    UInt32;
typedef signed int                      SInt32;
typedef float                           Float;
typedef double                          Double;
typedef Int8 Bool; //typedef bool Bool;
typedef char Char;

typedef __int64                         Int64;
typedef unsigned __int64                UInt64;
typedef signed __int64                  SInt64;

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

#define DEFAULT_SCREEN_WIDTH (640)
#define DEFAULT_SCREEN_HEIGHT (448)
#define SCREEN_WIDTH Float(RsGlobal.width)
#define SCREEN_HEIGHT Float(RsGlobal.height)
#define SCREEN_STRETCH_X(a)   Float( a * ( SCREEN_WIDTH / Float(DEFAULT_SCREEN_WIDTH)  ) )
#define SCREEN_STRETCH_Y(a)   Float( a * ( SCREEN_HEIGHT / Float(DEFAULT_SCREEN_HEIGHT) ) )
#define SCREEN_FROM_RIGHT(a)  Float( SCREEN_WIDTH - SCREEN_STRETCH_X(a) )
#define SCREEN_FROM_BOTTOM(a) Float( SCREEN_HEIGHT - SCREEN_STRETCH_Y(a) )

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
	union
	{
	    uint32 color32;
		struct { uint8 r, g, b, a; };
		struct { uint8 red, green, blue, alpha; };
#ifdef RWCORE_H
		struct  { RwRGBA rwRGBA; };
#endif
	};
	
	CRGBA(void) { }
	CRGBA(uint8 r, uint8 g, uint8 b, uint8 a) : r(r), g(g), b(b), a(a) { }
#ifdef RWCORE_H
	operator RwRGBA &(void)
	{
		return rwRGBA;
	}
	
	operator RwRGBA *(void)
	{
		return &rwRGBA;
	}
	
	operator RwRGBA (void) const
	{
		return rwRGBA;
	}
#endif
};

// inline float clamp(float v, float min, float max){ return v<min ? min : v>max ? max : v; }

inline float
sq(float x) { return x*x; }

#define SQR(x) ( x * x )

#define PI M_PI
#define DEGTORAD(x) ((x) * PI / 180.0f)
#define RADTODEG(x) ((x) * 180.0f / PI)


#if USE_PS2_RAND == TRUE
#define MY_RAND_MAX		65535
#else
#define MY_RAND_MAX		32767
#endif

int myrand(void);
void mysrand(unsigned int seed);

#define debug printf
#define ASSERT assert

#define _TODO(x)      
#define _TODOCONST(x) (x)

#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#define VALIDATE_OFFSET(struc, member, offset) static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")

#define clamp(v, a, b) (max(min(v, b), a))
//#define min(a, b) ((a) < (b) ? (a) : (b))
//#define max(a, b) ((a) > (b) ? (a) : (b))

#define PERCENT(x, p)                    ( ( Float(x) * ( Float(p) / 100.0f ) ) )
#define ARRAY_SIZE(array)                (sizeof(array) / sizeof(array[0]))
#define BIT(num)                         (1<<(num))