#include "common.h"

#include "NodeName.h"
#include "VisibilityPlugins.h"
#include "AnimBlendClumpData.h"
#include "AnimBlendAssociation.h"
#include "RpAnimBlend.h"

CAnimBlendClumpData *gpAnimBlendClump;

void FrameUpdateCallBack(AnimBlendFrameData *frame, void *arg);
void FrameUpdateCallBackWithVelocityExtraction(AnimBlendFrameData *frame, void *arg);
void FrameUpdateCallBackWith3dVelocityExtraction(AnimBlendFrameData *frame, void *arg);

void
FrameUpdateCallBack(AnimBlendFrameData *frame, void *arg)
{
	CVector vec, pos(0.0f, 0.0f, 0.0f);
	CQuaternion q, rot(0.0f, 0.0f, 0.0f, 0.0f);
	float totalBlendAmount = 0.0f;
	RwMatrix *mat = RwFrameGetMatrix(frame->frame);
	CAnimBlendNode **node;
	AnimBlendFrameUpdateData *updateData = (AnimBlendFrameUpdateData*)arg;

	if(frame->flag & AnimBlendFrameData::VELOCITY_EXTRACTION &&
	   gpAnimBlendClump->velocity){
		if(frame->flag & AnimBlendFrameData::VELOCITY_EXTRACTION_3D)
			FrameUpdateCallBackWith3dVelocityExtraction(frame, arg);
		else
			FrameUpdateCallBackWithVelocityExtraction(frame, arg);
		return;
	}

	if(updateData->foobar)
		for(node = updateData->nodes; *node; node++)
			if((*node)->sequence && (*node)->association->IsPartial())
				totalBlendAmount += (*node)->association->blendAmount;

	for(node = updateData->nodes; *node; node++){
		if((*node)->sequence){
			(*node)->Update(vec, q, 1.0f-totalBlendAmount);
			if((*node)->sequence->HasTranslation())
				pos += vec;
			rot += q;
		}
		++*node;
	}

	if((frame->flag & AnimBlendFrameData::IGNORE_ROTATION) == 0){
		RwMatrixSetIdentity(mat);

		float norm = rot.MagnitudeSqr();
		if(norm == 0.0f)
			rot.w = 1.0f;
		else
			rot *= 1.0f/Sqrt(norm);
		rot.Get(mat);
	}

	if((frame->flag & AnimBlendFrameData::IGNORE_TRANSLATION) == 0){
		mat->pos.x = pos.x;
		mat->pos.y = pos.y;
		mat->pos.z = pos.z;
		mat->pos.x += frame->resetPos.x;
		mat->pos.y += frame->resetPos.y;
		mat->pos.z += frame->resetPos.z;
	}
	RwMatrixUpdate(mat);
}

void
FrameUpdateCallBackWithVelocityExtraction(AnimBlendFrameData *frame, void *arg)
{
	CVector vec, pos(0.0f, 0.0f, 0.0f);
	CQuaternion q, rot(0.0f, 0.0f, 0.0f, 0.0f);
	float totalBlendAmount = 0.0f;
	float transx = 0.0f, transy = 0.0f;
	float curx = 0.0f, cury = 0.0f;
	float endx = 0.0f, endy = 0.0f;
	bool looped = false;
	RwMatrix *mat = RwFrameGetMatrix(frame->frame);
	CAnimBlendNode **node;
	AnimBlendFrameUpdateData *updateData = (AnimBlendFrameUpdateData*)arg;

	if(updateData->foobar)
		for(node = updateData->nodes; *node; node++)
			if((*node)->sequence && (*node)->association->IsPartial())
				totalBlendAmount += (*node)->association->blendAmount;

	for(node = updateData->nodes; *node; node++)
		if((*node)->sequence && (*node)->sequence->HasTranslation()){
			if((*node)->association->HasTranslation()){
				(*node)->GetCurrentTranslation(vec, 1.0f-totalBlendAmount);
				cury += vec.y;
				if((*node)->association->HasXTranslation())
					curx += vec.x;
			}
		}

	for(node = updateData->nodes; *node; node++){
		if((*node)->sequence){
			bool nodelooped = (*node)->Update(vec, q, 1.0f-totalBlendAmount);
			rot += q;
			if((*node)->sequence->HasTranslation()){
				pos += vec;
				if((*node)->association->HasTranslation()){
					transy += vec.y;
					if((*node)->association->HasXTranslation())
						transx += vec.x;
					looped |= nodelooped;
					if(nodelooped){
						(*node)->GetEndTranslation(vec, 1.0f-totalBlendAmount);
						endy += vec.y;
						if((*node)->association->HasXTranslation())
							endx += vec.x;
					}
				}
			}
		}
		++*node;
	}

	if((frame->flag & AnimBlendFrameData::IGNORE_ROTATION) == 0){
		RwMatrixSetIdentity(mat);

		float norm = rot.MagnitudeSqr();
		if(norm == 0.0f)
			rot.w = 1.0f;
		else
			rot *= 1.0f/Sqrt(norm);
		rot.Get(mat);
	}

	if((frame->flag & AnimBlendFrameData::IGNORE_TRANSLATION) == 0){
		gpAnimBlendClump->velocity->x = transx - curx;
		gpAnimBlendClump->velocity->y = transy - cury;
		if(looped){
			gpAnimBlendClump->velocity->x += endx;
			gpAnimBlendClump->velocity->y += endy;
		}
		mat->pos.x = pos.x - transx;
		mat->pos.y = pos.y - transy;
		mat->pos.z = pos.z;
		if(mat->pos.z >= -0.8f)
			if(mat->pos.z < -0.4f)
				mat->pos.z += (2.5f * mat->pos.z + 2.0f) * frame->resetPos.z;
			else
				mat->pos.z += frame->resetPos.z;
		mat->pos.x += frame->resetPos.x;
		mat->pos.y += frame->resetPos.y;
	}
	RwMatrixUpdate(mat);
}

// original code uses do loops?
void
FrameUpdateCallBackWith3dVelocityExtraction(AnimBlendFrameData *frame, void *arg)
{
	CVector vec, pos(0.0f, 0.0f, 0.0f);
	CQuaternion q, rot(0.0f, 0.0f, 0.0f, 0.0f);
	float totalBlendAmount = 0.0f;
	CVector trans(0.0f, 0.0f, 0.0f);
	CVector cur(0.0f, 0.0f, 0.0f);
	CVector end(0.0f, 0.0f, 0.0f);
	bool looped = false;
	RwMatrix *mat = RwFrameGetMatrix(frame->frame);
	CAnimBlendNode **node;
	AnimBlendFrameUpdateData *updateData = (AnimBlendFrameUpdateData*)arg;

	if(updateData->foobar)
		for(node = updateData->nodes; *node; node++)
			if((*node)->sequence && (*node)->association->IsPartial())
				totalBlendAmount += (*node)->association->blendAmount;

	for(node = updateData->nodes; *node; node++)
		if((*node)->sequence && (*node)->sequence->HasTranslation()){
			if((*node)->association->HasTranslation()){
				(*node)->GetCurrentTranslation(vec, 1.0f-totalBlendAmount);
				cur += vec;
			}
		}

	for(node = updateData->nodes; *node; node++){
		if((*node)->sequence){
			bool nodelooped = (*node)->Update(vec, q, 1.0f-totalBlendAmount);
			rot += q;
			if((*node)->sequence->HasTranslation()){
				pos += vec;
				if((*node)->association->HasTranslation()){
					trans += vec;
					looped |= nodelooped;
					if(nodelooped){
						(*node)->GetEndTranslation(vec, 1.0f-totalBlendAmount);
						end += vec;
					}
				}
			}
		}
		++*node;
	}

	if((frame->flag & AnimBlendFrameData::IGNORE_ROTATION) == 0){
		RwMatrixSetIdentity(mat);

		float norm = rot.MagnitudeSqr();
		if(norm == 0.0f)
			rot.w = 1.0f;
		else
			rot *= 1.0f/Sqrt(norm);
		rot.Get(mat);
	}

	if((frame->flag & AnimBlendFrameData::IGNORE_TRANSLATION) == 0){
		*gpAnimBlendClump->velocity = trans - cur;
		if(looped)
			*gpAnimBlendClump->velocity += end;
		mat->pos.x = (pos - trans).x + frame->resetPos.x;
		mat->pos.y = (pos - trans).y + frame->resetPos.y;
		mat->pos.z = (pos - trans).z + frame->resetPos.z;
	}
	RwMatrixUpdate(mat);
}
