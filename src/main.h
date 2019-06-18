#pragma once

struct GlobalScene
{
	RpWorld *world;
	RwCamera *camera;
};
extern GlobalScene &Scene;

extern uint8 work_buff[55000];
extern char gString[256];
extern wchar *gUString;

class CSprite2d;

void LoadingScreen(const char *str1, const char *str2, const char *splashscreen);
CSprite2d *LoadSplash(const char *name);
char *GetRandomSplashScreen(void);
