#include "common.h"

#ifdef CUSTOM_FRONTEND_OPTIONS
#include "frontendoption.h"
#include "Text.h"

int numCustomFrontendOptions = 0;
FrontendOption *customFrontendOptions;

int numCustomFrontendScreens = 0;
FrontendScreen* customFrontendScreens;

int numFrontendOptionReplacements = 0;
CMenuScreen::CMenuEntry* frontendOptionReplacements;

int lastOgScreen = MENUPAGES; // means no new pages

int optionCursor = -2;
int currentMenu;
bool optionOverwrite = false;

void ChangeScreen(int screen, int option, bool fadeIn)
{
	FrontEndMenuManager.m_nPrevScreen = FrontEndMenuManager.m_nCurrScreen;
	FrontEndMenuManager.m_nCurrScreen = screen;
	FrontEndMenuManager.m_nCurrOption = option;
	if (fadeIn)
		FrontEndMenuManager.m_nMenuFadeAlpha = 0;
}

void GoBack(bool fadeIn)
{
	int screen = !FrontEndMenuManager.m_bGameNotLoaded ?
		aScreens[FrontEndMenuManager.m_nCurrScreen].m_PreviousPage[1] : aScreens[FrontEndMenuManager.m_nCurrScreen].m_PreviousPage[0];
	int option = !FrontEndMenuManager.m_bGameNotLoaded ?
		aScreens[FrontEndMenuManager.m_nCurrScreen].m_ParentEntry[1] : aScreens[FrontEndMenuManager.m_nCurrScreen].m_ParentEntry[0];

	FrontEndMenuManager.ThingsToDoBeforeGoingBack();

	ChangeScreen(screen, option, fadeIn);
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
	uint8 page = -1;
	for (int i = 0; i < MENUPAGES; i++) {
		if (strcmp(aScreens[i].m_ScreenName, "") == 0 && aScreens[i].unk == 0)
			break;

		++page;
	}
	return page;
}

// Used before populating options, but effective in InitialiseChangedLanguageSettings and debugmenu
void
RemoveCustomFrontendOptions()
{
	if (numCustomFrontendOptions != 0) {

		for (int i = 0; i < MENUPAGES; i++) {
			for (int j = 0; j < NUM_MENUROWS; j++) {
				if (aScreens[i].m_aEntries[j].m_SaveSlot == SAVESLOT_CFO) {
					int ogOptionId = customFrontendOptions[aScreens[i].m_aEntries[j].m_TargetMenu].ogOptionId;

					if (customFrontendOptions[aScreens[i].m_aEntries[j].m_TargetMenu].type == FEOPTION_SELECT)
						free(customFrontendOptions[aScreens[i].m_aEntries[j].m_TargetMenu].rightTexts);

					if (ogOptionId == -1) {
						int k;
						for (k = j; k < NUM_MENUROWS - 1; k++) {
							memcpy(&aScreens[i].m_aEntries[k], &aScreens[i].m_aEntries[k + 1], sizeof(CMenuScreen::CMenuEntry));
						}
						aScreens[i].m_aEntries[k].m_Action = MENUACTION_NOTHING;
						aScreens[i].m_aEntries[k].m_SaveSlot = SAVESLOT_NONE;
						aScreens[i].m_aEntries[k].m_EntryName[0] = '\0';
						j--;
					} else {
						memcpy(&aScreens[i].m_aEntries[j], &frontendOptionReplacements[ogOptionId], sizeof(CMenuScreen::CMenuEntry));
					}
				}
			}
		}
		free(customFrontendOptions);
		numCustomFrontendOptions = 0;

		if (numFrontendOptionReplacements != 0) {
			free(frontendOptionReplacements);
			numFrontendOptionReplacements = 0;
		}
	}

	if (numCustomFrontendScreens == 0)
		return;

	for (int i = 0; i < MENUPAGES; i++) {
		if (i > lastOgScreen) {
			aScreens[i].m_ScreenName[0] = '\0';
			aScreens[i].unk = 0;
		}
	}
	free(customFrontendScreens);
	numCustomFrontendScreens = 0;
	lastOgScreen = MENUPAGES;
}

int8 RegisterNewScreen(char *name, int prevPage)
{
	if (lastOgScreen == MENUPAGES)
		lastOgScreen = GetLastMenuScreen();

	numCustomFrontendScreens++;
	if (numCustomFrontendScreens == 1)
		customFrontendScreens = (FrontendScreen*)malloc(5 * sizeof(FrontendScreen));
	else if (numCustomFrontendScreens % 5 == 1)
		customFrontendScreens = (FrontendScreen*)realloc(customFrontendScreens, (numCustomFrontendScreens + 4) * sizeof(FrontendScreen));

	assert(customFrontendScreens != nil && "Custom frontend screens can't be allocated");

	int id = lastOgScreen + numCustomFrontendScreens;
	assert(id < MENUPAGES && "No room for new custom frontend screens! Increase MENUPAGES");
	strncpy(aScreens[id].m_ScreenName, name, 8);
	aScreens[id].m_PreviousPage[0] = aScreens[id].m_PreviousPage[1] = prevPage;
	aScreens[id].unk = 1;
	return id;
}

int8 RegisterNewOption()
{
	numCustomFrontendOptions++;
	if (numCustomFrontendOptions == 1)
		customFrontendOptions = (FrontendOption*)malloc(5 * sizeof(FrontendOption));
	else if (numCustomFrontendOptions % 5 == 1)
		customFrontendOptions = (FrontendOption*)realloc(customFrontendOptions, (numCustomFrontendOptions + 4) * sizeof(FrontendOption));

	assert(customFrontendOptions != nil && "Custom frontend options can't be allocated");

	uint8 numOptions = GetNumberOfMenuOptions(currentMenu);
	uint8 curIdx;
	if (optionCursor < 0) {
		optionCursor = curIdx = numOptions + optionCursor + 1;
	} else 
		curIdx = optionCursor;

	if (!optionOverwrite) {
		if (aScreens[currentMenu].m_aEntries[curIdx].m_Action != MENUACTION_NOTHING) {
			for (int i = numOptions - 1; i >= curIdx; i--) {
				memcpy(&aScreens[currentMenu].m_aEntries[i + 1], &aScreens[currentMenu].m_aEntries[i], sizeof(CMenuScreen::CMenuEntry));
			}
		}
	}
	optionCursor++;

	if (optionOverwrite) {
		numFrontendOptionReplacements++;
		if (numFrontendOptionReplacements == 1)
			frontendOptionReplacements = (CMenuScreen::CMenuEntry*)malloc(5 * sizeof(CMenuScreen::CMenuEntry));
		else if (numFrontendOptionReplacements % 5 == 1)
			frontendOptionReplacements = (CMenuScreen::CMenuEntry*)realloc(frontendOptionReplacements, (numFrontendOptionReplacements + 4) * sizeof(CMenuScreen::CMenuEntry));

		memcpy(&frontendOptionReplacements[numFrontendOptionReplacements - 1], &aScreens[currentMenu].m_aEntries[curIdx], sizeof(CMenuScreen::CMenuEntry));
		customFrontendOptions[numCustomFrontendOptions - 1].ogOptionId = numFrontendOptionReplacements - 1;
	} else {
		customFrontendOptions[numCustomFrontendOptions - 1].ogOptionId = -1;
	}
	customFrontendOptions[numCustomFrontendOptions - 1].screen = currentMenu;

	aScreens[currentMenu].m_aEntries[curIdx].m_Action = MENUACTION_TRIGGERFUNC;
	aScreens[currentMenu].m_aEntries[curIdx].m_SaveSlot = SAVESLOT_CFO;
	aScreens[currentMenu].m_aEntries[curIdx].m_TargetMenu = numCustomFrontendOptions - 1;
	aScreens[currentMenu].m_aEntries[curIdx].m_EntryName[0] = 1; // just something to fool it
	return curIdx;
}

void FrontendOptionSetCursor(int screen, int8 option, bool overwrite)
{
	currentMenu = screen;
	optionCursor = option;
	optionOverwrite = overwrite;
}

void FrontendOptionAddBuiltinAction(const wchar* leftText, int action, ButtonPressFunc buttonPressFunc, ReturnPrevPageFunc returnPrevPageFunc) {
	int8 screenOptionOrder = RegisterNewOption();

	FrontendOption& option = customFrontendOptions[numCustomFrontendOptions - 1];

	// To fool the Frontend, we will still display the text passed via first param.
	switch (action) {
		case MENUACTION_SCREENRES:
			strcpy(aScreens[currentMenu].m_aEntries[screenOptionOrder].m_EntryName, "FED_RES");
			break;
		case MENUACTION_AUDIOHW:
			strcpy(aScreens[currentMenu].m_aEntries[screenOptionOrder].m_EntryName, "FEA_3DH");
			break;
	}
	aScreens[currentMenu].m_aEntries[screenOptionOrder].m_Action = action;
	option.type = FEOPTION_BUILTIN_ACTION;
	option.buttonPressFunc = buttonPressFunc;
	TextCopy(option.leftText, leftText);
	option.screenOptionOrder = screenOptionOrder;
	option.returnPrevPageFunc = returnPrevPageFunc;
	option.save = false;
}

void FrontendOptionAddSelect(const wchar* leftText, const wchar** rightTexts, int8 numRightTexts, int8 *var, bool onlyApplyOnEnter, ChangeFunc changeFunc, ReturnPrevPageFunc returnPrevPageFunc, bool save)
{
	int8 screenOptionOrder = RegisterNewOption();

	FrontendOption& option = customFrontendOptions[numCustomFrontendOptions - 1];
	option.type = FEOPTION_SELECT;
	TextCopy(option.leftText, leftText);
	option.rightTexts = (wchar**)malloc(numRightTexts * sizeof(wchar*));
	memcpy(option.rightTexts, rightTexts, numRightTexts * sizeof(wchar*));
	option.numRightTexts = numRightTexts;
	option.value = var;
	option.displayedValue = *var;
	option.lastSavedValue = *var;
	option.save = save;
	option.onlyApplyOnEnter = onlyApplyOnEnter;
	option.changeFunc = changeFunc;
	option.screenOptionOrder = screenOptionOrder;
	option.returnPrevPageFunc = returnPrevPageFunc;
}

void FrontendOptionAddDynamic(const wchar* leftText, DrawFunc drawFunc, int8 *var, ButtonPressFunc buttonPressFunc, ReturnPrevPageFunc returnPrevPageFunc, bool save)
{
	int8 screenOptionOrder = RegisterNewOption();

	FrontendOption& option = customFrontendOptions[numCustomFrontendOptions - 1];
	option.type = FEOPTION_DYNAMIC;
	option.drawFunc = drawFunc;
	option.buttonPressFunc = buttonPressFunc;
	TextCopy(option.leftText, leftText);
	option.value = var;
	option.save = save;
	option.screenOptionOrder = screenOptionOrder;
	option.returnPrevPageFunc = returnPrevPageFunc;
}

void FrontendOptionAddRedirect(const wchar* text, int to, int8 selectedOption, bool fadeIn)
{
	int8 screenOptionOrder = RegisterNewOption();

	FrontendOption &option = customFrontendOptions[numCustomFrontendOptions - 1];
	option.type = FEOPTION_REDIRECT;
	option.to = to;
	option.option = selectedOption;
	option.fadeIn = fadeIn;
	TextCopy(option.leftText, text);
	option.screenOptionOrder = screenOptionOrder;
	option.returnPrevPageFunc = nil;
	option.save = false;
}

void FrontendOptionAddBackButton(const wchar* text, bool fadeIn)
{
	int8 screenOptionOrder = RegisterNewOption();

	FrontendOption& option = customFrontendOptions[numCustomFrontendOptions - 1];
	option.type = FEOPTION_GOBACK;
	option.fadeIn = fadeIn;
	TextCopy(option.leftText, text);
	option.screenOptionOrder = screenOptionOrder;
	option.returnPrevPageFunc = nil;
	option.save = false;
}

uint8 FrontendScreenAdd(char* gxtKey, eMenuSprites sprite, int prevPage, int columnWidth, int headerHeight, int lineHeight,
	int8 font, float fontScaleX, float fontScaleY, int8 alignment, bool showLeftRightHelper, ReturnPrevPageFunc returnPrevPageFunc) {

	uint8 screenOrder = RegisterNewScreen(gxtKey, prevPage);

	FrontendScreen &screen = customFrontendScreens[numCustomFrontendScreens - 1];
	screen.id = screenOrder;
	screen.sprite = sprite;
	screen.prevPage = prevPage;
	strncpy(screen.name, gxtKey, 8);
	screen.columnWidth = columnWidth;
	screen.headerHeight = headerHeight;
	screen.lineHeight = lineHeight;
	screen.font = font;
	screen.fontScaleX = fontScaleX;
	screen.fontScaleY = fontScaleY;
	screen.alignment = alignment;
	screen.returnPrevPageFunc = returnPrevPageFunc;

	return screenOrder;
}
#endif