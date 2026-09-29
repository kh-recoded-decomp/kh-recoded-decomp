#include "nitro/types.h"

typedef struct CollisionObject {
    u8 pad_00[0xe];
    u16 groupMask;
    s32 handle;
    s32 ownerId;
    u8 pad_18[0x70];
} CollisionObject;

extern void func_01ff86fc(u32 value, void *destination, u32 size);

BOOL InitCollisionObject_02033c7c(CollisionObject *object, u16 groupMask, s32 ownerId) {
    func_01ff86fc(0, object, sizeof(CollisionObject));
    object->groupMask = groupMask;
    object->ownerId = ownerId;
    object->handle = -1;
    return TRUE;
}
