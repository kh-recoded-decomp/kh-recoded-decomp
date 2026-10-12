#pragma opt_common_subs off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct BlockPool BlockPool;
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

typedef struct BlockActor {
    u8 pad_00[0x10c];
    CollisionObject collision;
} BlockActor;

enum {
    STACK_ROOT = 1,
    STACK_INACTIVE = 0x8000
};

typedef struct StackedBlock {
    u32 state;
    BlockPool *pool;
    u8 pad_08[0x2a];
    u8 entityId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[0x10];
    u16 flags;
    s16 upperIndex;
    s16 lowerIndex;
    s16 baseIndex;
} StackedBlock;

extern StackedBlock *func_ov001_02086384(BlockPool *pool, int index);
extern StackedBlock *FindLiveNextBlock(StackedBlock *block);
extern BlockActor *ActorRegistry_GetEntityByIndex(u32 index);
extern void ResizeBoxCollisionObject(CollisionObject *object, fx32 sizeX,
                                     fx32 sizeY, fx32 sizeZ, s32 angle);
extern void Obj_SetPosition(BlockActor *actor, const VecFx32 *position);

void RefreshStackedBlockCollision(StackedBlock *block)
{
    StackedBlock *current;
    BlockActor *actor;
    fx32 height;

    if (block->flags & STACK_ROOT) {
        height = 0;
        current = block;
        for (;;) {
            if (!(current->flags & STACK_INACTIVE)) {
                height += 0x1800;
            }
            if (current->upperIndex < 0) {
                break;
            }
            current = func_ov001_02086384(current->pool, current->upperIndex);
        }
        if (height != 0) {
            actor = ActorRegistry_GetEntityByIndex(block->entityId);
            ResizeBoxCollisionObject(&actor->collision,
                                     0x1800, height, 0x1800, 0);
            Obj_SetPosition(actor, &block->position);
        }
    } else if (!(block->flags & STACK_INACTIVE)) {
        current = FindLiveNextBlock(block);
        if (current != NULL) {
            height = current->position.y + 0x1800;
        } else {
            height = func_ov001_02086384(block->pool, block->baseIndex)->position.y;
        }
        block->position.y = height;
        Obj_SetPosition(ActorRegistry_GetEntityByIndex(block->entityId), &block->position);
    }
}
