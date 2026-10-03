#include "nitro/types.h"

typedef struct RecordSlot {
    u8 pad_00[8];
    u16 flags;
} RecordSlot;

typedef struct FieldObject {
    u8 pad_00[0x30];
    u16 statusFlags;
    u8 slot;
    u8 pad_33[0x17];
    s8 state;
    u8 flags : 7;
    u8 flagsHigh : 1;
} FieldObject;

extern void func_02036974(int slot);
extern RecordSlot *func_02036810(int slot);
extern void func_02036924(int slot);
extern void CacheEntry_SetActive_02087258(FieldObject *object, BOOL active);
extern BOOL IsFieldFlagBit1Set_020a3d40(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);

void SetFieldObjectHidden_020a3c78(FieldObject *object, BOOL hidden)
{
    BOOL visible;
    BOOL busy;

    if (hidden) {
        object->flags |= 2;
        object->statusFlags &= ~0x10;
        object->statusFlags &= ~8;
        func_02036974(object->slot);
    } else {
        object->flags &= ~2;
        object->statusFlags |= 0x10;
        if (!(func_02036810(object->slot)->flags & 0x100)) {
            func_02036924(object->slot);
        }
        CacheEntry_SetActive_02087258(object, TRUE);
    }
    if (object->statusFlags & 4) {
        visible = FALSE;
        if (!IsFieldFlagBit1Set_020a3d40(object)) {
            busy = TRUE;
            if (object->state != 2 && object->state != 1) {
                busy = FALSE;
            }
            if (!busy) {
                visible = TRUE;
            }
        }
        ActorSlot_SetFlag8ByIndex_02036120(object->slot, visible);
    }
}
