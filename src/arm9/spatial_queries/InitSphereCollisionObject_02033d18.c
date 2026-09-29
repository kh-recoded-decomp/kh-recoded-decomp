#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct CollisionObject {
    u8 pad_00[0x24];
    CollisionShape shape;
    u8 pad_44[0x44];
} CollisionObject;

extern const VecFx32 data_02053438;
extern BOOL InitCollisionObject_02033c7c(CollisionObject *object, u16 groupMask, s32 ownerId);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern CollisionShape func_0203ad14(void *storage, const VecFx32 *center, fx32 radius);

BOOL InitSphereCollisionObject_02033d18(CollisionObject *object, u16 groupMask, s32 ownerId, fx32 radius) {
    InitCollisionObject_02033c7c(object, groupMask, ownerId);
    object->shape = func_0203ad14(NNSi_FndAllocFromDefaultHeap_0202a178(0x10), &data_02053438, radius);
    return TRUE;
}
