#define WITHD3D
#include "common.h"
#include "TimeCycle.h"

void
DefinedState(void)
{
	RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void*)rwTEXTUREADDRESSWRAP);
	RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
	RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEGOURAUD);
	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	RwRenderStateSet(rwRENDERSTATEALPHAPRIMITIVEBUFFER, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEBORDERCOLOR, (void*)RWRGBALONG(0, 0, 0, 255));
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
	RwRenderStateSet(rwRENDERSTATEFOGCOLOR,
		(void*)RWRGBALONG(CTimeCycle::GetFogRed(), CTimeCycle::GetFogGreen(), CTimeCycle::GetFogBlue(), 255));
	RwRenderStateSet(rwRENDERSTATEFOGTYPE, (void*)rwFOGTYPELINEAR);
	RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);

	// D3D stuff
	RwD3D8SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	RwD3D8SetRenderState(D3DRS_ALPHAREF, 2);
}

RwObject*
GetFirstObjectCallback(RwObject *object, void *data)
{
	*(RwObject**)data = object;
	return nil;
}

RwObject*
GetFirstObject(RwFrame *frame)
{
	RwObject *obj;

	obj = nil;
	RwFrameForAllObjects(frame, GetFirstObjectCallback, &obj);
	return obj;
}
