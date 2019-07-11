#include "common.h"
#include <rpskin.h>
#include "patcher.h"
#include "main.h"
#include "RwHelper.h"
#include "RpAnimBlend.h"
#include "AnimBlendClumpData.h"
#include "Directory.h"
#include "CutsceneMgr.h"
#include "Streaming.h"
#include "CutsceneHead.h"


CCutsceneHead::CCutsceneHead(CObject *obj)
{
	RpAtomic *atm;

	assert(RwObjectGetType(obj->m_rwObject) == rpCLUMP);
	m_pHeadNode = RpAnimBlendClumpFindFrame((RpClump*)obj->m_rwObject, "Shead")->frame;
	atm = (RpAtomic*)GetFirstObject(m_pHeadNode);
	if(atm){
		assert(RwObjectGetType(atm) == rpATOMIC);
		RpAtomicSetFlags(atm, RpAtomicGetFlags(atm) & ~rpATOMICRENDER);
	}
}

void
CCutsceneHead::CreateRwObject(void)
{
	RpAtomic *atm;

	CEntity::CreateRwObject();
	assert(RwObjectGetType(m_rwObject) == rpCLUMP);
	atm = GetFirstAtomic((RpClump*)m_rwObject);
	RpSkinAtomicSetHAnimHierarchy(atm, RpHAnimFrameGetHierarchy(GetFirstChild(RpClumpGetFrame((RpClump*)m_rwObject))));
}

void
CCutsceneHead::DeleteRwObject(void)
{
	CEntity::DeleteRwObject();
}

void
CCutsceneHead::ProcessControl(void)
{
	RpAtomic *atm;
	RpHAnimHierarchy *hier;

	CPhysical::ProcessControl();

	m_matrix.SetRotateY(PI/2);
	m_matrix = CMatrix(RwFrameGetLTM(m_pHeadNode)) * m_matrix;
	UpdateRwFrame();

	assert(RwObjectGetType(m_rwObject) == rpCLUMP);
	atm = GetFirstAtomic((RpClump*)m_rwObject);
	hier = RpSkinAtomicGetHAnimHierarchy(atm);
	RpHAnimHierarchyAddAnimTime(hier, CTimer::GetTimeStepNonClipped()/50.0f);
}

void
CCutsceneHead::Render(void)
{
	RpAtomic *atm;

	m_matrix.SetRotateY(PI/2);
	m_matrix = CMatrix(RwFrameGetLTM(m_pHeadNode)) * m_matrix;
	UpdateRwFrame();

	assert(RwObjectGetType(m_rwObject) == rpCLUMP);
	atm = GetFirstAtomic((RpClump*)m_rwObject);
	RpHAnimHierarchyUpdateMatrices(RpSkinAtomicGetHAnimHierarchy(atm));

	CObject::Render();
}

void
CCutsceneHead::PlayAnimation(const char *animName)
{
	RpAtomic *atm;
	RpHAnimHierarchy *hier;
	RpHAnimAnimation *anim;
	uint32 offset, size;
	RwStream *stream;

	assert(RwObjectGetType(m_rwObject) == rpCLUMP);
	atm = GetFirstAtomic((RpClump*)m_rwObject);
	hier = RpSkinAtomicGetHAnimHierarchy(atm);

	sprintf(gString, "%s.anm", animName);

	if(CCutsceneMgr::ms_pCutsceneDir->FindItem(gString, offset, size)){
		stream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, "ANIM\\CUTS.IMG");
		assert(stream);

		CStreaming::MakeSpaceFor(size*2048);
		CStreaming::ImGonnaUseStreamingMemory();

		RwStreamSkip(stream, offset*2048);
		if(RwStreamFindChunk(stream, rwID_HANIMANIMATION, nil, nil)){
			anim = RpHAnimAnimationStreamRead(stream);
			RpHAnimHierarchySetCurrentAnim(hier, anim);
		}

		CStreaming::IHaveUsedStreamingMemory();

		RwStreamClose(stream, nil);
	}
}

class CCutsceneHead_ : public CCutsceneHead
{
public:
	void CreateRwObject_(void) { CCutsceneHead::CreateRwObject(); }
	void DeleteRwObject_(void) { CCutsceneHead::DeleteRwObject(); }
	void ProcessControl_(void) { CCutsceneHead::ProcessControl(); }
	void Render_(void) { CCutsceneHead::Render(); }
};

STARTPATCHES
	InjectHook(0x4BA650, &CCutsceneHead_::CreateRwObject_, PATCH_JUMP);
	InjectHook(0x4BA690, &CCutsceneHead_::DeleteRwObject_, PATCH_JUMP);
	InjectHook(0x4BA760, &CCutsceneHead_::ProcessControl_, PATCH_JUMP);
	InjectHook(0x4BA800, &CCutsceneHead_::Render_, PATCH_JUMP);
	InjectHook(0x4BA6A0, &CCutsceneHead::PlayAnimation, PATCH_JUMP);
ENDPATCHES
