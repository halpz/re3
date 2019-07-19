#pragma once

struct GlobalScene
{
	RpWorld *world;
	RwCamera *camera;
};
extern GlobalScene &Scene;

extern uint8 work_buff[55000];
//extern char gString[256];
//extern char gString2[512];
//extern wchar gUString[256];
//extern wchar gUString2[256];
extern char *gString;
extern char *gString2;
extern wchar *gUString;
extern wchar *gUString2;
extern bool &b_FoundRecentSavedGameWantToLoad;

class CSprite2d;

void InitialiseGame(void);
void LoadingScreen(const char *str1, const char *str2, const char *splashscreen);
void LoadingIslandScreen(const char *levelName);
CSprite2d *LoadSplash(const char *name);
char *GetLevelSplashScreen(int level);
char *GetRandomSplashScreen(void);

void LittleTest(void);
