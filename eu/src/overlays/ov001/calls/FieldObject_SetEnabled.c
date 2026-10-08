#include "nitro/types.h"

typedef struct ObjectWork {
    u8 pad_00[0x8];
    u16 flags;
} ObjectWork;

struct FieldObject;

typedef struct FieldObjectClass {
    u8 pad_00[0x20];
    void (*onEnabledChanged)(struct FieldObject *object, BOOL enabled);
    u8 pad_24[0x40];
    s16 workIndex;
} FieldObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    FieldObjectClass *objectClass;
    ObjectWork *work;
    u8 pad_10[0x3e];
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
} FieldObject;

extern BOOL IsObjectFlagClear(FieldObject *object);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void ActorSlot_SetFlag8(ObjectWork *work, BOOL enabled);
extern BOOL Container_HasFlag1(ObjectWork *work);
extern void ActorSlot_PlaceAndLink(ObjectWork *work, int a, int b);
extern void ActorSlot_AddToWorld(ObjectWork *work);
extern void func_020369a8(ObjectWork *work);

void FieldObject_SetEnabled(FieldObject *object, BOOL enabled)
{
    BOOL wasEnabled;
    u16 saved;
    void (*hook)(FieldObject *object, BOOL enabled);

    wasEnabled = IsObjectFlagClear(object);
    if (wasEnabled == enabled) {
        return;
    }
    saved = ReadSessionPackedBits(object->saveBitOffset, object->saveBitCount) & 0xfffe;
    if (!enabled) {
        saved |= 1;
    }
    WriteSessionPackedBits(object->saveBitOffset, object->saveBitCount, saved);
    if ((object->flags & 4) && object->objectClass->workIndex >= 0) {
        if (enabled) {
            ActorSlot_SetFlag8(object->work, TRUE);
            if (!Container_HasFlag1(object->work)) {
                ActorSlot_PlaceAndLink(object->work, 0, 0);
            }
            if (!(object->work->flags & 0x100)) {
                ActorSlot_AddToWorld(object->work);
            }
        } else {
            ActorSlot_SetFlag8(object->work, FALSE);
            if (object->work->flags & 0x100) {
                func_020369a8(object->work);
            }
        }
    }
    hook = object->objectClass->onEnabledChanged;
    if (hook != NULL) {
        hook(object, enabled);
    }
}
