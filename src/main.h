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

void LoadingScreen(const char *str1, const char *str2, const char *splashscreen);
