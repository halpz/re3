#pragma once

class CSmokeTrail {
	CVector m_pos[16];
	float m_density[16];
	int m_time[16];
	char m_unused[536];
	int m_seed;
public:
	void Render(void);
	void RegisterPoint(CVector position, float a);
	void Init(int num);
};

class CSmokeTrails {
	static CSmokeTrail aSmoke[3];
public:
	static bool CigOn;
	static void Update(void);
	static void Render(void);
	static void Init(void);
};

