#include "common.h"
#include "patcher.h"
#include "Messages.h"

WRAPPER void CMessages::Display(void) { EAXJMP(0x529800); }
WRAPPER void CMessages::ClearAllMessagesDisplayedByGame(void) { EAXJMP(0x52B670); }
WRAPPER int CMessages::WideStringCopy(wchar* dst, wchar* src, unsigned short size) { EAXJMP(0x5294B0); }
WRAPPER char CMessages::WideStringCompare(wchar* str1, wchar* str2, unsigned short size) { EAXJMP(0x529510); }
WRAPPER void CMessages::InsertNumberInString(wchar* src, int n1, int n2, int n3, int n4, int n5, int n6, wchar* dst) { EAXJMP(0x52A1A0); }
WRAPPER void CMessages::InsertPlayerControlKeysInString(wchar* src) { EAXJMP(0x52A490); }
WRAPPER int CMessages::GetWideStringLength(wchar* src) { EAXJMP(0x529490); }
WRAPPER void CMessages::AddBigMessage(wchar* key, uint32 time, uint16 pos) { EAXJMP(0x529EB0);  }
WRAPPER void CMessages::AddBigMessageQ(wchar* key, uint32 time, uint16 pos) { EAXJMP(0x529F60); }
WRAPPER void CMessages::AddBigMessageWithNumber(wchar* key, uint32 time, uint16 pos, int n1, int n2, int n3, int n4, int n5, int n6) { EAXJMP(0x52AD10); }
WRAPPER void CMessages::AddBigMessageWithNumberQ(wchar* key, uint32 time, uint16 pos, int n1, int n2, int n3, int n4, int n5, int n6) { EAXJMP(0x52AE00); }
WRAPPER void CMessages::AddMessage(wchar* key, uint32 time, uint16 pos) { EAXJMP(0x529900); }
WRAPPER void CMessages::AddMessageJumpQ(wchar* key, uint32 time, uint16 pos) { EAXJMP(0x529A10); }
WRAPPER void CMessages::AddMessageSoon(wchar* key, uint32 time, uint16 pos) { EAXJMP(0x529AF0); }
WRAPPER void CMessages::AddMessageWithNumber(wchar* key, uint32 time, uint16 pos, int n1, int n2, int n3, int n4, int n5, int n6) { EAXJMP(0x52A850); }
WRAPPER void CMessages::AddMessageJumpQWithNumber(wchar* key, uint32 time, uint16 pos, int n1, int n2, int n3, int n4, int n5, int n6) { EAXJMP(0x52A9A0); }
WRAPPER void CMessages::AddMessageSoonWithNumber(wchar* key, uint32 time, uint16 pos, int n1, int n2, int n3, int n4, int n5, int n6) { EAXJMP(0x52AAC0); }
WRAPPER void CMessages::ClearMessages() { EAXJMP(0x529CE0); }
WRAPPER void CMessages::Init() { EAXJMP(0x529310); }
WRAPPER void CMessages::Process() { EAXJMP(0x529580); }
tPreviousBrief *CMessages::PreviousBriefs = (tPreviousBrief *)0x713C08;
tMessage *CMessages::BriefMessages = (tMessage *)0x8786E0;
tBigMessage *CMessages::BIGMessages = (tBigMessage *)0x773628;
