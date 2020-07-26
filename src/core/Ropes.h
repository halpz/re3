#pragma once

class CRope
{
public:
	bool m_bActive;
	bool m_bWasRegistered;
	bool m_unk;
	uintptr m_id;
	uint32 m_updateTimer;
	CVector m_pos[32];
	CVector m_speed[32];

	void Update(void);
	void Render(void);
};

class CRopes
{
	static CRope aRopes[8];

public:

	static void Init(void);
	static void Update(void);
	static void Render(void);
	static bool RegisterRope(uintptr id, CVector pos, bool setUpdateTimer);
	static void SetSpeedOfTopNode(uintptr id, CVector speed);
	static bool FindCoorsAlongRope(uintptr id, float t, CVector *coors);
	static bool CreateRopeWithSwatComingDown(CVector pos);
};
