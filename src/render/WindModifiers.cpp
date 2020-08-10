#include "common.h"
#include "WindModifiers.h"
#include "Camera.h"
#include "General.h"

#define MAX_HEIGHT_DIST 40.0f
#define MIN_FADE_DIST 20.0f
#define MAX_FADE_DIST 50.0f

CWindModifiers Array[16];
int32 CWindModifiers::Number;

void
CWindModifiers::RegisterOne(CVector pos, int32 type = 1)
{
	if (CWindModifiers::Number < 16 && (pos - TheCamera.GetPosition()).Magnitude() < 100.0f) {
		Array[Number].m_pos = pos;
		Array[Number].m_type = type;
		Number++;
	}
}

bool
CWindModifiers::FindWindModifier(CVector pos, float *x, float *y)
{
	bool bWasWindModifierFound = false;
	CVector2D dir;
	for (int i = 0; i < Number; i++) {
		if (Array[i].m_type == 1) {
			float zDist = Abs(15.0f + pos.z - Array[i].m_pos.z);

			if (zDist < MAX_HEIGHT_DIST) {
				float dist = (pos - Array[i].m_pos).Magnitude();
				if (dist < MAX_FADE_DIST) {
					float distFade = dist < MIN_FADE_DIST ? 1.0f : 1.0f - (dist - MIN_FADE_DIST) / (MAX_FADE_DIST - MIN_FADE_DIST);
					float heightFade = 1.0f - zDist / MAX_HEIGHT_DIST;
					dir = (pos - Array[i].m_pos) * heightFade / dist;
					bWasWindModifierFound = true;
				}
			}
		}
	}

	if (bWasWindModifierFound) {
		float directionMult = ((CGeneral::GetRandomNumber() & 0x1F) - 16) * 0.0035f + 1.0f;
		*x += dir.x * directionMult;
		*y += dir.y * directionMult;
	}

	return bWasWindModifierFound;
}
