#pragma once

#ifdef VALIDATE_SAVE_SIZE
extern int32 _saveBufCount;
#define INITSAVEBUF _saveBufCount = 0;
#define VALIDATESAVEBUF(b) assert(_saveBufCount == b);
#else
#define INITSAVEBUF
#define VALIDATESAVEBUF(b)
#endif

inline void
SkipSaveBuf(uint8 *&buf, int32 skip)
{
	buf += skip;
#ifdef VALIDATE_SAVE_SIZE
	_saveBufCount += skip;
#endif
}

template <typename T>
inline void
ReadSaveBuf(T* out, uint8 *&buf)
{
	*out = *(T *)buf;
	SkipSaveBuf(buf, sizeof(T));
}

template <typename T>
inline T *
WriteSaveBuf(uint8 *&buf, const T &value)
{
	T *p = (T *)buf;
	*p = value;
	SkipSaveBuf(buf, sizeof(T));
	return p;
}

#define SAVE_HEADER_SIZE (4 * sizeof(char) + sizeof(uint32))

#define WriteSaveHeader(buf, a, b, c, d, size)                                                                                                                 \
	WriteSaveBuf(buf, a);                                                                                                                                  \
	WriteSaveBuf(buf, b);                                                                                                                                  \
	WriteSaveBuf(buf, c);                                                                                                                                  \
	WriteSaveBuf(buf, d);                                                                                                                                  \
	WriteSaveBuf(buf, (uint32)size);

#ifdef VALIDATE_SAVE_SIZE
#define CheckSaveHeader(buf, a, b, c, d, size) {                                                                                                                 \
	char _C; uint32 _size;\
	ReadSaveBuf(&_C, buf);\
	assert(_C == a);\
	ReadSaveBuf(&_C, buf);\
	assert(_C == b);\
	ReadSaveBuf(&_C, buf);\
	assert(_C == c);\
	ReadSaveBuf(&_C, buf);\
	assert(_C == d);\
	ReadSaveBuf(&_size, buf);\
	assert(_size == size);\
	}
#else
#define CheckSaveHeader(buf, a, b, c, d, size) SkipSaveBuf(buf, 8);
#endif