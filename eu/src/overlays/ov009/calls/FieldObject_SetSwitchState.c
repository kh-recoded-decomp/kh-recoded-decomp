#include "nitro/types.h"

typedef struct FieldObjectClass {
    u8 pad_00[0x46];
    u16 objectCount;
} FieldObjectClass;

typedef struct FieldObject {
    struct FieldObject *prev;
    struct FieldObject *next;
    FieldObjectClass *objectClass;
    void *work;
    u8 pad_10[4];
    void *stateHandler;
    u8 pad_18[0x36];
    u16 flags;
    u8 pad_50[8];
    int state;
} FieldObject;

extern FieldObject *GetStridedBufferEntry(FieldObjectClass *objectClass, int index);
extern void SetObjectAnimTrack(FieldObject *object, int track);
extern void FieldObject_SetSavedValue(FieldObject *object, u32 value);
extern void func_ov009_020a0ab0(void);
extern void func_ov009_020a0ad8(void);
extern void func_ov009_020a0ae4(void);

void FieldObject_SetSwitchState(FieldObject *object, int state)
{
    int count;
    int offCount;
    int i;

    switch (state) {
    case 0:
        object->stateHandler = func_ov009_020a0ab0;
        count = object->objectClass->objectCount;
        offCount = 0;
        for (i = 0; i < count; i++) {
            if (GetStridedBufferEntry(object->objectClass, i)->state == 0) {
                offCount++;
            }
        }
        if (offCount == 1) {
            SetObjectAnimTrack(object, 2);
        } else {
            SetObjectAnimTrack(object, 1);
        }
        object->flags |= 0x10;
        break;
    case 1:
        object->stateHandler = func_ov009_020a0ad8;
        SetObjectAnimTrack(object, 0);
        object->flags &= ~0x10;
        break;
    case 2:
        object->stateHandler = func_ov009_020a0ae4;
        FieldObject_SetSavedValue(object, 1);
        SetObjectAnimTrack(object, 0);
        object->flags &= ~0x10;
        if (object->state != 2) {
            count = object->objectClass->objectCount;
            for (i = 0; i < count; i++) {
                FieldObject *other = GetStridedBufferEntry(object->objectClass, i);
                if (other->state == 1) {
                    FieldObject_SetSwitchState(other, 0);
                    break;
                }
            }
        }
        break;
    }
    object->state = state;
}
