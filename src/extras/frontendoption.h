#pragma once
#include "common.h"

#ifdef CUSTOM_FRONTEND_OPTIONS
#include "Frontend.h"

// Warning:
//		All of the code relies on that you won't use more then NUM_MENUROWS(18) options on one page.
//		Also congrats if you can make 18 options visible at once.

// About texts:
//		All text parameters accept wchar(including hardcoded wchar* and TheText.Get)
//		except FrontendScreenAdd(it's char[8] by the design of Frontend).
//		All texts reload if custom options reloaded too, which includes language changes and via live reload feature in debug menu!

// Execute direction:
//		All of the calls below eventually manipulate the aScreens array, so keep in mind to add/replace options in order,
//		i.e. don't set cursor to 8 first and then 3.

// Live reload:
//		You can add/change/undo the new options in-game if you use VS. Change what you want, build the changed bits via "Edit and Continue",
//		and hit the "Reload custom frontend options" from debug menu. Or call CustomFrontendOptionsPopulate() from somewhere else.


// -- Option types
//
// Static/select:	You allocate the variable, pass it to function and game sets it from user input among the strings given to function,
//					then you can handle ChangeFunc(only called on enter if onlyApplyOnEnter set, or set immediately)
//					and ReturnPrevPageFunc optionally. You can store the option in gta3.set if you pass true to corresponding parameter.
//
// Dynamic:			Passing variable to function is only needed if you want to store it, otherwise you should do
//					all the operations with ButtonPressFunc, this includes allocating the variable.
//					Left-side text is passed while creating and static, but ofc right-side text is dynamic -
//					you should return it in DrawFunc, which is called on every draw. ReturnPrevPageFunc is also here if needed.
//
// Redirect:		Redirection to another screen. selectedOption parameter is the highlighted option user will see after the redirection.
//
// Built-in action:	As the name suggests, any action that game has built-in. But as an extra you can set the option text,
//					and can be informed on button press/focus loss via buttonPressFunc. ReturnPrevPageFunc is also here.

#define FEOPTION_SELECT 0
#define FEOPTION_DYNAMIC 1
#define FEOPTION_REDIRECT 2
#define FEOPTION_GOBACK 3
#define FEOPTION_BUILTIN_ACTION 4

// -- Returned via ButtonPressFunc() action param.
#define FEOPTION_ACTION_LEFT 0
#define FEOPTION_ACTION_RIGHT 1
#define FEOPTION_ACTION_SELECT 2
#define FEOPTION_ACTION_FOCUSLOSS 3

// -- Passed via FrontendScreenAdd()
#define FESCREEN_CENTER 0
#define FESCREEN_LEFT_ALIGN 1
#define FESCREEN_RIGHT_ALIGN 2

// -- Callbacks

// pretty much in everything I guess, and optional in all of them
typedef void (*ReturnPrevPageFunc)();

// for static options
typedef void (*ChangeFunc)(int8 displayedValue); // called before updating the value.
												// only called on enter if onlyApplyOnEnter set, otherwise called on every value change

// for dynamic options
typedef wchar* (*DrawFunc)(bool* disabled, bool userHovering); // you must return a pointer for right text.
															// you can also set *disabled if you want to gray it out.
typedef void (*ButtonPressFunc)(int8 action); // see FEOPTION_ACTIONs above

struct FrontendScreen
{
	int id;
	char name[8];
	eMenuSprites sprite;
	int prevPage;
	int columnWidth;
	int headerHeight;
	int lineHeight;
	int8 font;
	float fontScaleX;
	float fontScaleY;
	int8 alignment;
	bool showLeftRightHelper;
	ReturnPrevPageFunc returnPrevPageFunc;
};

struct FrontendOption
{
	int8 type;
	int8 screenOptionOrder;
	int32 screen;
	wchar leftText[64];
	ReturnPrevPageFunc returnPrevPageFunc;
	int8* value;
	int8 displayedValue; // only if onlyApplyOnEnter enabled for now
	bool save;
	int32 ogOptionId; // for replacements, see overwrite parameter of SetCursor
	
	union {
		// Only for dynamic / built-in action
		struct {
			DrawFunc drawFunc;
			ButtonPressFunc buttonPressFunc;
		};

		// Only for static/select
		struct {
			wchar** rightTexts;
			int8 numRightTexts;
			bool onlyApplyOnEnter;
			ChangeFunc changeFunc;
			int8 lastSavedValue; // only if onlyApplyOnEnter enabled
		};

		// Only for redirect
		struct {
			int to;
			int8 option;
			bool fadeIn;
		};
	};
};

// -- Internal things
void RemoveCustomFrontendOptions();
void CustomFrontendOptionsPopulate();

extern int lastOgScreen; // for reloading

extern int numCustomFrontendOptions;
extern FrontendOption* customFrontendOptions;

extern int numCustomFrontendScreens;
extern FrontendScreen* customFrontendScreens;

// -- To be used in ButtonPressFunc / ChangeFunc(this one would be weird):
void ChangeScreen(int screen, int option = 0, bool fadeIn = true);
void GoBack(bool fadeIn = true);

uint8 GetNumberOfMenuOptions(int screen);

// -- Placing the cursor to append/overwrite option
//
// Done via FrontendOptionSetCursor(screen, position, overwrite = false), parameters explained below:
// Screen:			as the name suggests. Also accepts the screen IDs returned from FrontendScreenAdd.
// Option:			if positive, next AddOption call will put the option to there and progress the cursor.
//					if negative, cursor will be placed on bottom-(pos+1), so -1 means the very bottom, -2 means before the back button etc.
// Overwrite:		Use to overwrite the options, not appending a new one. AddOption calls will still progress the cursor.

void FrontendOptionSetCursor(int screen, int8 option, bool overwrite = false);

// var is optional in AddDynamic, you can enable save parameter if you pass one, otherwise pass nil/0
void FrontendOptionAddBuiltinAction(const wchar* leftText, int action, ButtonPressFunc buttonPressFunc, ReturnPrevPageFunc returnPrevPageFunc);
void FrontendOptionAddSelect(const wchar* leftText, const wchar** rightTexts, int8 numRightTexts, int8 *var, bool onlyApplyOnEnter, ChangeFunc changeFunc, ReturnPrevPageFunc returnPrevPageFunc, bool save = false);
void FrontendOptionAddDynamic(const wchar* leftText, DrawFunc rightTextDrawFunc, int8 *var, ButtonPressFunc buttonPressFunc, ReturnPrevPageFunc returnPrevPageFunc, bool save = false);
void FrontendOptionAddRedirect(const wchar* text, int to, int8 selectedOption = 0, bool fadeIn = true);
void FrontendOptionAddBackButton(const wchar* text, bool fadeIn = true);

uint8 FrontendScreenAdd(char* gxtKey, eMenuSprites sprite, int prevPage, int columnWidth, int headerHeight, int lineHeight, int8 font, float fontScaleX, float fontScaleY, int8 alignment, bool showLeftRightHelper, ReturnPrevPageFunc returnPrevPageFunc = nil);
#endif