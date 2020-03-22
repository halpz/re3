#include "common.h"
#include "patcher.h"
#include "SceneEdit.h"

WRAPPER void CSceneEdit::Update(void) { EAXJMP(0x585570); }
WRAPPER void CSceneEdit::Init(void) { EAXJMP(0x585170); }
