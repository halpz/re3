#pragma once
#include "common.h"

#ifdef CUSTOM_FRONTEND_OPTIONS
#include "Frontend.h"

// Warning: All of the code relies on that you won't use more then NUM_MENUROWS(18) options on one page. Also congrats if you can make 18 options visible at once.


// Static/select:	User allocates variable, passes it to function and it's set automatically from input among the strings given to function,
//					then you can handle ChangeFunc and ReturnPrevPageFunc if needed.
//
// Dynamic:			Function doesn't accept value pointer, user should do operations with handling ButtonPressFunc.
//					Right-side text can be set via DrawFunc, which is called on every draw. ReturnPrevPageFunc is also here if needed.

#define FEOPTION_SELECT 0
#define FEOPTION_DYNAMIC 1
#define FEOPTION_REDIRECT 2
#define FEOPTION_GOBACK 3

#define FEOPTION_ACTION_LEFT 0
#define FEOPTION_ACTION_RIGHT 1
#define FEOPTION_ACTION_SELECT 2
#define FEOPTION_ACTION_FOCUSLOSS 3

void RemoveCustomFrontendOptions();
void CustomFrontendOptionsPopulate();

// for static and dynamic options
typedef void (*ReturnPrevPageFunc)();

// for static options
typedef void (*ChangeFunc)(int8 displayedValue); // called before updating the value

// for dynamic options
typedef wchar* (*DrawFunc)(bool* disabled); // should return pointer to right text. *disabled = true will make it dark yellow
typedef void (*ButtonPressFunc)(int8 action); // see FEOPTION_ACTIONs above

struct FrontendOption
{
	int8 type;
	int8 screenOptionOrder;
	eMenuScreen screen;
	const wchar* leftText;
	ReturnPrevPageFunc returnPrevPageFunc;
	
	union {
		// Only for dynamic
		struct {
			DrawFunc drawFunc;
			ButtonPressFunc buttonPressFunc;
		};

		// Only for static/select
		struct {
			const wchar** rightTexts;
			int8 numRightTexts;
			int8 *value;
			int8 displayedValue; // if onlyApplyOnEnter enabled
			bool onlyApplyOnEnter;
			ChangeFunc changeFunc;
		};

		// Only for redirect
		struct {
			eMenuScreen to;
			int8 option;
			bool fadeIn;
		};
	};
};

extern int numCustomFrontendOptions;
extern FrontendOption* customFrontendOptions;

// To be used in ButtonPressFunc / ChangeFunc(but that would be weird):
void ChangeScreen(eMenuScreen screen, int option = 0, bool fadeIn = true);
void GoBack(bool fadeIn = true);

// If option is positive number, all calls will increase it before using it (you can think it as cursor). -1 means before the back button, -2 is end of page
void FrontendOptionSetPosition(eMenuScreen screen, int8 option = -1);

void FrontendOptionAddSelect(const wchar* leftText, const wchar** rightTexts, int8 numRightTexts, int8 *var, bool onlyApplyOnEnter, ChangeFunc changeFunc, ReturnPrevPageFunc returnPrevPageFunc);
void FrontendOptionAddDynamic(const wchar* leftText, DrawFunc rightTextDrawFunc, ButtonPressFunc buttonPressFunc, ReturnPrevPageFunc returnPrevPageFunc);
void FrontendOptionAddRedirect(const wchar* text, eMenuScreen to, int8 selectedOption = 0, bool fadeIn = true);
void FrontendOptionAddBackButton(const wchar* text, bool fadeIn = true);
#endif