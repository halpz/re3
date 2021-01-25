#pragma once

#include "SimpleModelInfo.h"
#include "WeaponType.h"

class CWeaponModelInfo : public CSimpleModelInfo
{
	union {
		int32 m_animFileIndex;
		char *m_animFileName;
	};

	static base::cRelocatableChunkClassInfo msClassInfo;
	static CWeaponModelInfo msClassInstance;

public:
	CWeaponModelInfo(void) : CSimpleModelInfo(MITYPE_WEAPON) { m_animFileIndex = -1; }

	virtual void SetAnimFile(const char *file);
	virtual void ConvertAnimFileIndex(void);
	virtual int GetAnimFileIndex(void) { return m_animFileIndex; }

	virtual void RcWriteThis(base::cRelocatableChunkWriter &writer);
	virtual void RcWriteEmpty(base::cRelocatableChunkWriter &writer);

	//virtual void SetAtomic(int n, RpAtomic *atomic);
	
	void Init(void);
	void SetWeaponInfo(int32 weaponId);
	eWeaponType GetWeaponInfo(void);
};
