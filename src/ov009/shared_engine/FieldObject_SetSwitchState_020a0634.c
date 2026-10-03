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

extern FieldObject *func_ov001_0207f4b4(FieldObjectClass *objectClass, int index);
extern void SetObjectAnimTrack_0207f8d0(FieldObject *object, int track);
extern void FieldObject_SetSavedValue_0207f9c8(FieldObject *object, u32 value);
extern void func_ov009_020a0a90(void);
extern void MsgQueue_GetHeap_020a0ab8(void);
extern void MsgQueue_GetHeap_020a0ac4(void);

void FieldObject_SetSwitchState_020a0634(FieldObject *object, int state)
{
    int count;
    int offCount;
    int i;

    switch (state) {
    case 0:
        object->stateHandler = func_ov009_020a0a90;
        count = object->objectClass->objectCount;
        offCount = 0;
        for (i = 0; i < count; i++) {
            if (func_ov001_0207f4b4(object->objectClass, i)->state == 0) {
                offCount++;
            }
        }
        if (offCount == 1) {
            SetObjectAnimTrack_0207f8d0(object, 2);
        } else {
            SetObjectAnimTrack_0207f8d0(object, 1);
        }
        object->flags |= 0x10;
        break;
    case 1:
        object->stateHandler = MsgQueue_GetHeap_020a0ab8;
        SetObjectAnimTrack_0207f8d0(object, 0);
        object->flags &= ~0x10;
        break;
    case 2:
        object->stateHandler = MsgQueue_GetHeap_020a0ac4;
        FieldObject_SetSavedValue_0207f9c8(object, 1);
        SetObjectAnimTrack_0207f8d0(object, 0);
        object->flags &= ~0x10;
        if (object->state != 2) {
            count = object->objectClass->objectCount;
            for (i = 0; i < count; i++) {
                FieldObject *other = func_ov001_0207f4b4(object->objectClass, i);
                if (other->state == 1) {
                    FieldObject_SetSwitchState_020a0634(other, 0);
                    break;
                }
            }
        }
        break;
    }
    object->state = state;
}
