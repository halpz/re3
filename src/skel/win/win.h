#if (!defined(_PLATFORM_WIN_H))
#define _PLATFORM_WIN_H

#if (!defined(RSREGSETBREAKALLOC))
#define RSREGSETBREAKALLOC(_name) /* No op */
#endif /* (!defined(RSREGSETBREAKALLOC)) */

enum eGameState
{
	GS_START_UP = 0,
	GS_INIT_LOGO_MPEG,
	GS_LOGO_MPEG,
	GS_INIT_INTRO_MPEG,
	GS_INTRO_MPEG,
	GS_INIT_ONCE,
	GS_INIT_FRONTEND,
	GS_FRONTEND,
	GS_INIT_PLAYING_GAME,
	GS_PLAYING_GAME,
};

enum eWinVersion
{
	OS_WIN95 = 0,
	OS_WIN98,
	oS_WINNT,
	OS_WIN2000,
	OS_WINXP,
};

extern RwUInt32 &gGameState;

#ifdef    __cplusplus
extern "C"
{
#endif                          /* __cplusplus */

extern LRESULT      CALLBACK
MainWndProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

#ifdef    __cplusplus
}
#endif                          /* __cplusplus */


#endif /* (!defined(_PLATFORM_WIN_H)) */
