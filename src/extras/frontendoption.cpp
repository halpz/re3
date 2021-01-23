#include "common.h"

#ifdef CUSTOM_FRONTEND_OPTIONS
#include "Frontend.h"
#include "Text.h"

int lastOgScreen = MENUPAGES; // means no new pages

int numCustomFrontendOptions = 0;
int numCustomFrontendScreens = 0;

int optionCursor = -2;
int currentMenu;
bool optionOverwrite = false;

void GoBack()
{
	FrontEndMenuManager.SwitchToNewScreen(-1);
}

uint8
GetNumberOfMenuOptions(int screen)
{
	uint8 Rows = 0;
	for (int i = 0; i < NUM_MENUROWS; i++) {
		if (aScreens[screen].m_aEntries[i].m_Action == MENUACTION_NOTHING)
			break;

		++Rows;
	}
	return Rows;
}

uint8
GetLastMenuScreen()
{
	int8 page = -1;
	for (int i = 0; i < MENUPAGES; i++) {
		if (strcmp(aScreens[i].m_ScreenName, "") == 0 && aScreens[i].m_PreviousPage == MENUPAGE_NONE)
			break;

		++page;
	}
	return page;
}

int8 RegisterNewScreen(const char *name, int prevPage, ReturnPrevPageFunc returnPrevPageFunc)
{
	if (lastOgScreen == MENUPAGES)
		lastOgScreen = GetLastMenuScreen();

	numCustomFrontendScreens++;
	int id = lastOgScreen + numCustomFrontendScreens;
	assert(id < MENUPAGES && "No room for new custom frontend screens! Increase MENUPAGES");
	strncpy(aScreens[id].m_ScreenName, name, 8);
	aScreens[id].m_PreviousPage = prevPage;
	aScreens[id].returnPrevPageFunc = returnPrevPageFunc;
	return id;
}

int8 RegisterNewOption()
{
	numCustomFrontendOptions++;
	uint8 numOptions = GetNumberOfMenuOptions(currentMenu);
	uint8 curIdx;
	if (optionCursor < 0) {
		optionCursor = curIdx = numOptions + optionCursor + 1;
	} else 
		curIdx = optionCursor;

	if (!optionOverwrite) {
		if (aScreens[currentMenu].m_aEntries[curIdx].m_Action != MENUACTION_NOTHING) {
			for (int i = numOptions - 1; i >= curIdx; i--) {
				memcpy(&aScreens[currentMenu].m_aEntries[i + 1], &aScreens[currentMenu].m_aEntries[i], sizeof(CMenuScreenCustom::CMenuEntry));
			}
		}
	}
	optionCursor++;
	return curIdx;
}

void FrontendOptionSetCursor(int screen, int8 option, bool overwrite)
{
	currentMenu = screen;
	optionCursor = option;
	optionOverwrite = overwrite;
}

void FrontendOptionAddBuiltinAction(const char* gxtKey, uint16 x, uint16 y, uint8 align, int action, int targetMenu, int saveSlot) {
	int8 screenOptionOrder = RegisterNewOption();

	CMenuScreenCustom::CMenuEntry &option = aScreens[currentMenu].m_aEntries[screenOptionOrder];

	// We can't use custom text on those :shrug:
	switch (action) {
		case MENUACTION_SCREENRES:
			strcpy(option.m_EntryName, "FED_RES");
			break;
		case MENUACTION_AUDIOHW:
			strcpy(option.m_EntryName, "FEA_3DH");
			break;
		default:
			strncpy(option.m_EntryName, gxtKey, 8);
			break;
	}
	option.m_X = x;
	option.m_Y = y;
	option.m_Align = align;
	option.m_Action = action;
	option.m_SaveSlot = saveSlot;
	option.m_TargetMenu = targetMenu;
}

void FrontendOptionAddSelect(const char* gxtKey, uint16 x, uint16 y, uint8 align, const char** rightTexts, int8 numRightTexts, int8 *var, bool onlyApplyOnEnter, ChangeFunc changeFunc, const char* saveCat, const char* saveName, bool disableIfGameLoaded)
{	
	int8 screenOptionOrder = RegisterNewOption();

	CMenuScreenCustom::CMenuEntry &option = aScreens[currentMenu].m_aEntries[screenOptionOrder];
	option.m_Action = MENUACTION_CFO_SELECT;
	option.m_X = x;
	option.m_Y = y;
	option.m_Align = align;
	strncpy(option.m_EntryName, gxtKey, 8);
	option.m_CFOSelect = new CCFOSelect();
	option.m_CFOSelect->rightTexts = (char**)malloc(numRightTexts * sizeof(char*));
	memcpy(option.m_CFOSelect->rightTexts, rightTexts, numRightTexts * sizeof(char*));
	option.m_CFOSelect->numRightTexts = numRightTexts;
	option.m_CFOSelect->value = var;
	if (var) {
		option.m_CFOSelect->displayedValue = *var;
		option.m_CFOSelect->lastSavedValue = *var;
	}
	option.m_CFOSelect->saveCat = saveCat;
	option.m_CFOSelect->save = saveName;
	option.m_CFOSelect->onlyApplyOnEnter = onlyApplyOnEnter;
	option.m_CFOSelect->changeFunc = changeFunc;
	option.m_CFOSelect->disableIfGameLoaded = disableIfGameLoaded;
}

void FrontendOptionAddDynamic(const char* gxtKey, uint16 x, uint16 y, uint8 align, DrawFunc drawFunc, int8 *var, ButtonPressFunc buttonPressFunc, const char* saveCat, const char* saveName)
{
	int8 screenOptionOrder = RegisterNewOption();

	CMenuScreenCustom::CMenuEntry &option = aScreens[currentMenu].m_aEntries[screenOptionOrder];
	option.m_Action = MENUACTION_CFO_DYNAMIC;
	option.m_X = x;
	option.m_Y = y;
	option.m_Align = align;
	strncpy(option.m_EntryName, gxtKey, 8);
	option.m_CFODynamic = new CCFODynamic();
	option.m_CFODynamic->drawFunc = drawFunc;
	option.m_CFODynamic->buttonPressFunc = buttonPressFunc;
	option.m_CFODynamic->value = var;
	option.m_CFODynamic->saveCat = saveCat;
	option.m_CFODynamic->save = saveName;
}

// lineHeight = 0 means game will use MENU_DEFAULT_LINE_HEIGHT
uint8 FrontendScreenAdd(const char* gxtKey, int prevPage, int lineHeight, bool showLeftRightHelper, ReturnPrevPageFunc returnPrevPageFunc) {

	uint8 screenOrder = RegisterNewScreen(gxtKey, prevPage, returnPrevPageFunc);

	CCustomScreenLayout *screen = new CCustomScreenLayout();
	aScreens[screenOrder].layout = screen;
	screen->lineHeight = lineHeight;
	screen->showLeftRightHelper = showLeftRightHelper;

	return screenOrder;
}
#endif
