#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *work;
    void *resource;
    u8 pad_14[0x24];
    u8 classKind;
    u8 pad_39[0x15];
    u16 flags;
} FieldObject;

typedef struct FieldObjectClass {
    u8 pad_00[0x18];
    void (*onObjectDestroy)(FieldObject *object);
    void (*onClassDestroy)(struct FieldObjectClass *objectClass);
    u8 pad_20[0x26];
    u16 slotCount;
} FieldObjectClass;

extern FieldObject *func_ov001_0207f4b4(FieldObjectClass *objectClass, int slotIndex);
extern void Obj_ConditionalShutdown_020368c8(void *object, u16 arg);
extern void ReleaseResourceAndDetach_0202eee8(void *resource);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

void FieldObjectClass_Destroy_0207f3d0(FieldObjectClass *objectClass)
{
    u16 count = objectClass->slotCount;
    FieldObject *object;
    int i;

    for (i = 0; i < count; i++) {
        object = func_ov001_0207f4b4(objectClass, i);
        if (object->flags & 1) {
            if (objectClass->onObjectDestroy != NULL) {
                objectClass->onObjectDestroy(object);
            }
            if (object->work != NULL) {
                Obj_ConditionalShutdown_020368c8(object->work, object->classKind);
                NNSi_FndFreeFromDefaultHeap_0202a1c4(object->work);
                object->work = NULL;
            }
            if (object->resource != NULL) {
                ReleaseResourceAndDetach_0202eee8(object->resource);
                NNSi_FndFreeFromDefaultHeap_0202a1c4(object->resource);
                object->resource = NULL;
            }
        }
    }
    if (objectClass->onClassDestroy != NULL) {
        objectClass->onClassDestroy(objectClass);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(objectClass);
}
