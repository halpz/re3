#pragma once

class CKeyGen
{
	static uint32 keyTable[256];
public:
	static uint32 GetKey(const char *str, int size);
	static uint32 GetKey(const char *str);
	static uint32 GetUppercaseKey(const char *str);
	static uint32 AppendStringToKey(uint32 key, const char *str);
};