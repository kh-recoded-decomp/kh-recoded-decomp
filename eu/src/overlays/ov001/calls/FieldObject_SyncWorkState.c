#include "nitro/types.h"

typedef struct WorkSlots {
    u8 pad_00[0x6];
    s16 kinds[5];
    u8 pad_10[0xCC];
    s16 counts[5];
} WorkSlots;

typedef struct ObjectWork {
    u8 pad_00[0x10];
    WorkSlots slots;
} ObjectWork;

typedef struct FieldObjectClass {
    u8 pad_00[0x64];
    s16 workIndex;
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    FieldObjectClass *objectClass;
    ObjectWork *work;
    u8 pad_10[0x3E];
    u16 flags;
    u8 pad_50[0x3];
    u8 slotKind;
    u8 pad_54[0x6];
    u8 stateBits;
} FieldObject;

extern BOOL Container_HasFlag3(ObjectWork *work);
extern void FieldObject_SetEnabled(FieldObject *object, BOOL enabled);

void FieldObject_SyncWorkState(FieldObject *object)
{
    int slotIndex;
    WorkSlots *slots;

    if (object->objectClass->workIndex < 0) {
        return;
    }
    slots = &object->work->slots;
    for (slotIndex = 0; slotIndex < 5; slotIndex++) {
        if (slots->counts[(u16)slotIndex] > 0) {
            object->slotKind = slots->kinds[(u16)slotIndex];
            break;
        }
    }
    if (Container_HasFlag3(object->work)) {
        object->stateBits &= ~2;
        object->flags |= 0x30;
        FieldObject_SetEnabled(object, TRUE);
    } else {
        object->stateBits |= 2;
        object->flags &= ~0x30;
        object->stateBits &= ~1;
    }
}
