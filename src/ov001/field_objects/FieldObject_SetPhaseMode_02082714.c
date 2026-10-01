#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0xc];
    void *work;
    u32 unk_10;
    void *updateFunc;
    u8 pad_18[0x36];
    u16 flags;
    u8 pad_50[8];
    u32 mode : 15;
    u32 pendingDisable : 1;
    u32 unk_58_16 : 16;
    u8 pad_5c[4];
    int phase;
} FieldObject;

extern void FieldObject_SetEnabled_0207f6f4(FieldObject *object, BOOL enabled);
extern void ActorSlot_Unlink_02035c48(void *slot);
extern int AdvanceWrappedPhase_02082440(FieldObject *object);
extern int func_ov001_02082468(FieldObject *object);

void FieldObject_SetPhaseMode_02082714(FieldObject *object, int mode)
{
    object->mode = mode;
    switch (mode) {
    case 0:
        object->updateFunc = AdvanceWrappedPhase_02082440;
        FieldObject_SetEnabled_0207f6f4(object, TRUE);
        return;
    case 1:
        object->updateFunc = func_ov001_02082468;
        object->phase = 0;
        FieldObject_SetEnabled_0207f6f4(object, TRUE);
        return;
    case 2:
        if (object->flags & 4) {
            ActorSlot_Unlink_02035c48(object->work);
            FieldObject_SetEnabled_0207f6f4(object, FALSE);
            return;
        }
        object->pendingDisable = TRUE;
        return;
    }
}
