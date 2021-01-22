#include "common.h"

#include "main.h"
#include "ModelInfo.h"
#include "Object.h"
#include "FileMgr.h"
#include "ObjectData.h"

CObjectInfo CObjectData::ms_aObjectInfo[NUMOBJECTINFO];

// Another ugly file reader
void
CObjectData::Initialise(const char *filename)
{
	char *p, *lp;
	char line[1024], name[256];
	int id;
	float percentSubmerged;
	int damageEffect, responseCase, camAvoid;
	CBaseModelInfo *mi;
	
	ms_aObjectInfo[0].m_fMass = 99999.0f;
	ms_aObjectInfo[0].m_fTurnMass = 99999.0f;
	ms_aObjectInfo[0].m_fAirResistance = 0.99f;
	ms_aObjectInfo[0].m_fElasticity = 0.1f;
	ms_aObjectInfo[0].m_fBuoyancy = GRAVITY * ms_aObjectInfo[0].m_fMass * 2.0f;
	ms_aObjectInfo[0].m_fUprootLimit = 0.0f;
	ms_aObjectInfo[0].m_fCollisionDamageMultiplier = 1.0f;
	ms_aObjectInfo[0].m_nCollisionDamageEffect = 0;
	ms_aObjectInfo[0].m_nSpecialCollisionResponseCases = 0;
	ms_aObjectInfo[0].m_bCameraToAvoidThisObject = false;

	ms_aObjectInfo[1].m_fMass = 99999.0f;
	ms_aObjectInfo[1].m_fTurnMass = 99999.0f;
	ms_aObjectInfo[1].m_fAirResistance = 0.99f;
	ms_aObjectInfo[1].m_fElasticity = 0.1f;
	ms_aObjectInfo[1].m_fBuoyancy = ms_aObjectInfo[0].m_fBuoyancy;
	ms_aObjectInfo[1].m_fUprootLimit = 0.0f;
	ms_aObjectInfo[1].m_fCollisionDamageMultiplier = 1.0f;
	ms_aObjectInfo[1].m_nCollisionDamageEffect = 0;
	ms_aObjectInfo[1].m_nSpecialCollisionResponseCases = 0;
	ms_aObjectInfo[1].m_bCameraToAvoidThisObject = true;

	ms_aObjectInfo[2].m_fMass = 99999.0f;
	ms_aObjectInfo[2].m_fTurnMass = 99999.0f;
	ms_aObjectInfo[2].m_fAirResistance = 0.99f;
	ms_aObjectInfo[2].m_fElasticity = 0.1f;
	ms_aObjectInfo[2].m_fBuoyancy = ms_aObjectInfo[0].m_fBuoyancy;
	ms_aObjectInfo[2].m_fUprootLimit = 0.0f;
	ms_aObjectInfo[2].m_fCollisionDamageMultiplier = 1.0f;
	ms_aObjectInfo[2].m_nCollisionDamageEffect = 0;
	ms_aObjectInfo[2].m_bCameraToAvoidThisObject = false;
	ms_aObjectInfo[2].m_nSpecialCollisionResponseCases = 4;

	ms_aObjectInfo[3].m_fMass = 99999.0f;
	ms_aObjectInfo[3].m_fTurnMass = 99999.0f;
	ms_aObjectInfo[3].m_fAirResistance = 0.99f;
	ms_aObjectInfo[3].m_fElasticity = 0.1f;
	ms_aObjectInfo[3].m_fBuoyancy = ms_aObjectInfo[0].m_fBuoyancy;
	ms_aObjectInfo[3].m_fUprootLimit = 0.0f;
	ms_aObjectInfo[3].m_fCollisionDamageMultiplier = 1.0f;
	ms_aObjectInfo[3].m_nCollisionDamageEffect = 0;
	ms_aObjectInfo[3].m_nSpecialCollisionResponseCases = 4;
	ms_aObjectInfo[3].m_bCameraToAvoidThisObject = true;

	CFileMgr::SetDir("");
	CFileMgr::LoadFile(filename, work_buff, sizeof(work_buff), "r");

	id = 4;
	p = (char*)work_buff;
	while(*p != '*'){
		// skip over white space and comments
		while(*p == ' ' || *p == '\n' || *p == '\r' || *p == ';')
			if(*p == ';')
				while(*p != '\n' && *p != '*')
					p++;
			else
				p++;

		if(*p == '*')
			break;

		// read one line
		lp = line;
		while(*p != '\n' && *p != '*'){
			*lp++ = *p == ',' ? ' ' : *p;
			p++;
		}
		if(*p == '\n')
			p++;
#ifdef FIX_BUGS
		*lp = '\0';	// FIX: game wrote '\n' here
#else
		*lp = '\n';
#endif

		assert(id < NUMOBJECTINFO);
		sscanf(line, "%s %f %f %f %f %f %f %f %d %d %d", name,
			&ms_aObjectInfo[id].m_fMass,
			&ms_aObjectInfo[id].m_fTurnMass,
			&ms_aObjectInfo[id].m_fAirResistance,
			&ms_aObjectInfo[id].m_fElasticity,
			&percentSubmerged,
			&ms_aObjectInfo[id].m_fUprootLimit,
			&ms_aObjectInfo[id].m_fCollisionDamageMultiplier,
			&damageEffect, &responseCase, &camAvoid);

		ms_aObjectInfo[id].m_fBuoyancy = 100.0f/percentSubmerged * GRAVITY *ms_aObjectInfo[id].m_fMass;
		ms_aObjectInfo[id].m_nCollisionDamageEffect = damageEffect;
		ms_aObjectInfo[id].m_nSpecialCollisionResponseCases = responseCase;
		ms_aObjectInfo[id].m_bCameraToAvoidThisObject = camAvoid;

		mi = CModelInfo::GetModelInfo(name, nil);
		if (mi) {
			if (ms_aObjectInfo[0].m_fMass != ms_aObjectInfo[id].m_fMass
				|| ms_aObjectInfo[0].m_fCollisionDamageMultiplier != ms_aObjectInfo[id].m_fCollisionDamageMultiplier
				|| ms_aObjectInfo[0].m_nCollisionDamageEffect != ms_aObjectInfo[id].m_nCollisionDamageEffect
				|| ((ms_aObjectInfo[0].m_nSpecialCollisionResponseCases != ms_aObjectInfo[id].m_nSpecialCollisionResponseCases)
					&& (ms_aObjectInfo[2].m_nSpecialCollisionResponseCases != ms_aObjectInfo[id].m_nSpecialCollisionResponseCases))) {
				mi->SetObjectID(id++);
			} else if (ms_aObjectInfo[0].m_nSpecialCollisionResponseCases == ms_aObjectInfo[id].m_nSpecialCollisionResponseCases) {
				if (ms_aObjectInfo[0].m_bCameraToAvoidThisObject == ms_aObjectInfo[id].m_bCameraToAvoidThisObject)
					mi->SetObjectID(0);
				else
					mi->SetObjectID(1);
			} else if (ms_aObjectInfo[2].m_bCameraToAvoidThisObject == ms_aObjectInfo[id].m_bCameraToAvoidThisObject)
				mi->SetObjectID(2);
			else 
				mi->SetObjectID(3);
		} else
			debug("CObjectData: Cannot find object %s\n", name);
	}
}

void
CObjectData::SetObjectData(int32 modelId, CObject &object)
{
	CObjectInfo *objinfo;

	if(CModelInfo::GetModelInfo(modelId)->GetObjectID() == -1)
		return;

	objinfo = &ms_aObjectInfo[CModelInfo::GetModelInfo(modelId)->GetObjectID()];

	object.m_fMass = objinfo->m_fMass;
	object.m_fTurnMass = objinfo->m_fTurnMass;
	object.m_fAirResistance = objinfo->m_fAirResistance;
	object.m_fElasticity = objinfo->m_fElasticity;
	object.m_fBuoyancy = objinfo->m_fBuoyancy;
	object.m_fUprootLimit = objinfo->m_fUprootLimit;
	object.m_fCollisionDamageMultiplier = objinfo->m_fCollisionDamageMultiplier;
	object.m_nCollisionDamageEffect = objinfo->m_nCollisionDamageEffect;
	object.m_nSpecialCollisionResponseCases = objinfo->m_nSpecialCollisionResponseCases;
	object.m_bCameraToAvoidThisObject = objinfo->m_bCameraToAvoidThisObject;
	if(object.m_fMass >= 99998.0f){
		object.bInfiniteMass = true;
		object.m_phy_flagA08 = true;
		object.bAffectedByGravity = false;
		object.bExplosionProof = true;
	}
}
