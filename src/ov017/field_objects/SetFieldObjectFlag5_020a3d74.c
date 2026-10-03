#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x4a];
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
    u8 pad_4C[4];
    s32 kind : 16;
    s32 subKind : 12;
    s32 bit28 : 1;
    s32 hitsLeft : 3;
} FieldObject;

extern void func_ov017_020a3c78(FieldObject *object, int arg);

void SetFieldObjectFlag5_020a3d74(FieldObject *object, BOOL enable)
{
    if (object->subKind == 2) {
        return;
    }
    if (enable) {
        object->flags |= 0x20;
        return;
    }
    if (object->flags & 0x20) {
        object->flags &= ~0x20;
        if ((u8)(s8)(object->state - 1) > 1) {
            func_ov017_020a3c78(object, 0);
        }
    }
}
