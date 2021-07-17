#include "common.h"

#include "Timer.h"
#include "Font.h"
#include "Frontend.h"
#include "RwHelper.h"
#include "Camera.h"
#include "Text.h"
#include "Credits.h"
#include "Pad.h"

bool CCredits::bCreditsGoing;
uint32 CCredits::CreditsStartTime;

void
CCredits::Init(void)
{
	Stop();
}

void
CCredits::Start(void)
{
	bCreditsGoing = true;
	CreditsStartTime = CTimer::GetTimeInMilliseconds();
}

void
CCredits::Stop(void)
{
	bCreditsGoing = false;
}

void
CCredits::PrintCreditSpace(float space, uint32 &line)
{
	line += space * 25.0f;
}

void
CCredits::PrintCreditText(float scaleX, float scaleY, wchar *text, uint32 &lineoffset, float scrolloffset)
{
	CPad::UpdatePads();
	if (CPad::GetPad(0)->GetCrossJustDown())
		bCreditsGoing = false;
	else {
		float start = DEFAULT_SCREEN_HEIGHT + 20.0f;
		float y = lineoffset + start - scrolloffset;
		if (y > 20.0f && DEFAULT_SCREEN_HEIGHT - 20.0f > y) {
			CFont::SetScale(SCREEN_SCALE_X(scaleX), SCREEN_SCALE_Y(scaleY));
			CFont::SetColor(CRGBA(0, 0, 0, 255));
			CFont::PrintString(SCREEN_WIDTH / 2.0f, SCREEN_SCALE_Y(y), (uint16*)text);
			CFont::SetColor(CRGBA(220, 220, 220, 220));
			CFont::PrintString(SCREEN_WIDTH / 2.0f - SCREEN_SCALE_X(1.0f), SCREEN_SCALE_Y(y - 1.0f), (uint16*)text);
		}
		lineoffset += scaleY*25.0f;
	}
}

void
CCredits::Render(void)
{
	uint32 lineoffset;
	float scrolloffset;

	if(!bCreditsGoing || FrontEndMenuManager.m_bMenuActive)
		return;

	DefinedState();
	lineoffset = 0;
	scrolloffset = (CTimer::GetTimeInMilliseconds() - CreditsStartTime) / 24.0f;
	CFont::SetJustifyOff();
	CFont::SetBackgroundOff();
	CFont::SetCentreSize(SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH * 0.75f));
	CFont::SetCentreOn();
	CFont::SetPropOn();
	CFont::SetFontStyle(FONT_STANDARD);

    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED001"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED002"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED003"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED004"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED005"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED006"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED007"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED008"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED025"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED026"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED027"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED028"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED029"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED030"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED031"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD031A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD031B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD031C"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD031D"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD031E"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD024A"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED024"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED023"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD023A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD023B"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED018"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED019"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD018A"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD019A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD019B"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED020"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED021"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD022A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED022"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD022B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD022C"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED032"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED033"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD032A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED034"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED035"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED036"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED037"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD037A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD037B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD037C"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD041B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED042"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED039"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED044"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED040"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD042A"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED142"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD142A"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED009"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED010"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED011"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED012"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED013"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD013A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD013B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD013C"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED089"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED090"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED347"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED047"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED048"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED049"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED348"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED050"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED051"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED052"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED053"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED054"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED055"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED056"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD056A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD056B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD056C"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD056D"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED349"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED350"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED351"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED352"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED353"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED354"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED355"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED356"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED357"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED359"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED360"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED361"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED362"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED363"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED364"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED365"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED366"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED367"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED368"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED369"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED370"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED371"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED372"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED373"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED256"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED257"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED258"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED057"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED058"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD057A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED059"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD060A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD060B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD060C"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD002A"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED003"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD001A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD001B"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED060"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED061"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED062"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED063"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED064"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED069"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED070"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED065"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED066"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED067"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED068"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD071A"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD072A"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED091"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED094"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED095"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED097"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED098"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD098A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD098B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD098C"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED099"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED096"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED273"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD092A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED092"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD092B"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED073"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED074"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED076"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED075"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED077"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED078"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED081"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED082"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED079"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED080"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED083"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED084"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD084A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD084B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD084C"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD084D"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD084E"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED085"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED086"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD086A"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED087"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED088"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD088A"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD088B"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD088C"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD088D"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD088E"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD088F"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD088G"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED107"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED108"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED109"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED110"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD110A"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED111"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED112"), lineoffset, scrolloffset);

    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED113"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED114"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED115"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED116"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED117"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED118"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED119"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED120"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED121"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED122"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED123"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED124"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED125"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED126"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED127"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED128"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED129"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);

    CFont::SetCentreSize(SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH * 0.8f));

    PrintCreditText(1.1f, 0.8f, TheText.Get("CRD111A"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);

    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED130"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED131"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED132"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED133"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED134"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD134A"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD134B"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD134C"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD134D"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD134E"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD134F"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD134G"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD134H"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD134I"), lineoffset, scrolloffset);

    CFont::SetCentreSize(SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH * 0.7f));

    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED135"), lineoffset, scrolloffset);

    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH || FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_SPANISH)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD136A"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD137A"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED138"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED066"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD138B"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED139"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(1.1f, 0.8f, TheText.Get("CRED140"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_FRENCH)
        PrintCreditSpace(0.5f, lineoffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140A"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140B"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140C"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140D"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140E"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140F"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140G"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140H"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140I"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140J"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140K"), lineoffset, scrolloffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD140L"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    
    CFont::SetCentreSize(SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH * 0.85f));

    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED259"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED260"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED261"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED262"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED263"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED264"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED265"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED266"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED141"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD141A"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD141B"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED143"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED144"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED145"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED146"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED147"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED148"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED149"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED150"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED151"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED152"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED153"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED154"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED155"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED156"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED157"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED158"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED159"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED160"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED161"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED162"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED163"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED164"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED165"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED166"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED167"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED168"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED169"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED170"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED171"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED172"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);

    CFont::SetCentreSize(SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH * 0.75f));

    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED217"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED218"), lineoffset, scrolloffset);
    PrintCreditSpace(1.0f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRD218A"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED219"), lineoffset, scrolloffset);
    PrintCreditSpace(1.0f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED220"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED221"), lineoffset, scrolloffset);
    PrintCreditSpace(1.0f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED222"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED223"), lineoffset, scrolloffset);
    PrintCreditSpace(1.0f, lineoffset);
    PrintCreditText(1.1f, 1.1f, TheText.Get("CRED224"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED227"), lineoffset, scrolloffset);
    PrintCreditSpace(1.0f, lineoffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED228"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED229"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD229A"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD229B"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED274"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED275"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED276"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED277"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED278"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED279"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED280"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED281"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED282"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED283"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED284"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED285"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED286"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED287"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED288"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED289"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED290"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED291"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED292"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED293"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED294"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED295"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED296"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED297"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED298"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED299"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED300"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED301"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED302"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED303"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED304"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED305"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED306"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED307"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED308"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED309"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED310"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED314"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED315"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED316"), lineoffset, scrolloffset);
    PrintCreditSpace(1.0f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED317"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED318"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED319"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED320"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED321"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED322"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED323"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED324"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED325"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED326"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED327"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED328"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED329"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED330"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED331"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED332"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    
    CFont::SetCentreSize(SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH * 0.8f));

    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED333"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED334"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED335"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED336"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED337"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED338"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED339"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED340"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED341"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED342"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditSpace(1.0f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD344A"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED344"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED345"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRD345A"), lineoffset, scrolloffset);
    PrintCreditSpace(1.0f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED346"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(1.0f, lineoffset);

    PrintCreditSpace(1.5f, lineoffset);

    CFont::SetCentreSize(SCREEN_SCALE_X(DEFAULT_SCREEN_WIDTH * 0.75f));

    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED267"), lineoffset, scrolloffset);
    PrintCreditSpace(0.5f, lineoffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED268"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED269"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED270"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED271"), lineoffset, scrolloffset);
    PrintCreditText(0.65f, 0.65f, TheText.Get("CRED272"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditText(0.95f, 0.7f, TheText.Get("CRED230"), lineoffset, scrolloffset);
    if (FrontEndMenuManager.m_PrefsLanguage == CMenuManager::LANGUAGE_ITALIAN)
        PrintCreditSpace(0.5f, lineoffset);

    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED231"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED232"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED233"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED234"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED235"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED236"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED237"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED238"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED239"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED240"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED241"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED242"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED243"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED244"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED245"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED246"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED247"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED248"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED249"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED358"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED250"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED251"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED252"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRD251A"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRD252A"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED253"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED254"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED374"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED375"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED376"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED377"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED378"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED379"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED380"), lineoffset, scrolloffset);
    PrintCreditText(0.95f, 0.95f, TheText.Get("CRED381"), lineoffset, scrolloffset);
    PrintCreditSpace(1.5f, lineoffset);
    PrintCreditSpace(1.5f, lineoffset);
    CFont::DrawFonts();
#ifdef CUTSCENE_BORDERS_SWITCH
    if (CMenuManager::m_PrefsCutsceneBorders)
#endif
	if(TheCamera.m_WideScreenOn)
		TheCamera.DrawBordersForWideScreen();

#ifdef FIX_BUGS
	if(lineoffset + DEFAULT_SCREEN_HEIGHT - scrolloffset < -10.0f)
#else
	if(lineoffset + SCREEN_HEIGHT - scrolloffset < -10.0f)
#endif
	{
		bCreditsGoing = false;
	}
}

bool CCredits::AreCreditsDone(void)
{
	return !bCreditsGoing;
}
