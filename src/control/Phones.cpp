#include "common.h"
#include "patcher.h"
#include "Phones.h"

WRAPPER void PhonePutDownCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x42F570); }
WRAPPER void PhonePickUpCB(CAnimBlendAssociation *assoc, void *arg) { EAXJMP(0x42F470); }
