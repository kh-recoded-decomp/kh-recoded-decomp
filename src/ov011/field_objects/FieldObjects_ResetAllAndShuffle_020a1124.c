#include "nitro/types.h"

typedef struct FieldObjectClass {
    u8 pad_00[0x44];
    u16 objectSize;
    u16 objectCount;
    void *objects;
} FieldObjectClass;

extern void *func_ov001_0207f4b4(FieldObjectClass *objectClass, int slotIndex);
extern void func_ov011_020a10c4(void *object);
extern void func_ov011_020a0f30(FieldObjectClass *objectClass);

void FieldObjects_ResetAllAndShuffle_020a1124(FieldObjectClass *objectClass)
{
    int slotIndex;
    int count = objectClass->objectCount;

    for (slotIndex = 0; slotIndex < count; slotIndex++) {
        func_ov011_020a10c4(func_ov001_0207f4b4(objectClass, slotIndex));
    }
    func_ov011_020a0f30(objectClass);
}
