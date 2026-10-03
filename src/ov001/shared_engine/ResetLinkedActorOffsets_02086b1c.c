#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NodeDef {
    u8 pad_00[8];
    u16 flags;
} NodeDef;

typedef struct LinkNode LinkNode;

struct LinkNode {
    LinkNode *next;
    u8 pad_04[4];
    NodeDef *def;
    u8 pad_0c[0x32 - 0x0c];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
};

typedef struct LinkList {
    u8 pad_00[8];
    LinkNode *head;
} LinkList;

typedef struct CollisionWorld {
    u8 pad_00[4];
    int **tree;
} CollisionWorld;

typedef struct LinkedActor {
    u32 flags;
    u8 pad_004[0x10c - 0x004];
    u8 collision[0xc];
    u8 collisionFlags;
    u8 pad_119[0x134 - 0x119];
    u8 baseBox[0x1c];
    VecFx32 offset;
    u8 box[0x18];
} LinkedActor;

extern LinkList *data_ov001_020a04dc;
extern const VecFx32 data_02053438;

extern CollisionWorld *func_02036230(void);
extern LinkedActor *func_02036240(u32 id);
extern BOOL IsNodeFlagBitClear_020872b8(LinkNode *node);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void SetCollisionObjectPosition_02033f48(void *object, const VecFx32 *position);
extern void QuadTree_ReinsertNodeIfFlagSet_02033f10(int *tree, void *node);

void ResetLinkedActorOffsets_02086b1c(void)
{
    LinkNode *node = data_ov001_020a04dc->head;
    CollisionWorld *world = func_02036230();
    LinkNode *next;
    LinkedActor *actor;

    while (node != NULL) {
        next = node->next;
        if (IsNodeFlagBitClear_020872b8(node) && (node->def->flags & 0x100)) {
            actor = func_02036240(node->actorId);
            if (world != NULL && !(actor->flags & 0x10) && (actor->flags & 8)) {
                actor->offset = data_02053438;
                OffsetBoxByDelta_0203ac70(actor->baseBox, actor->box, &actor->offset);
                SetCollisionObjectPosition_02033f48(actor->collision, &node->position);
                actor->collisionFlags |= 1;
                QuadTree_ReinsertNodeIfFlagSet_02033f10(*world->tree, actor->collision);
            }
        }
        node = next;
    }
}
