#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x4c];
    VecFx32 offset;
} ChildLayout;

typedef struct {
    u8 pad_00[0x10];
    u8 base[0xa8];
    VecFx32 position;
} ChildObject;

typedef struct {
    void *owner;
    ChildObject *object;
    int layoutIndex;
    VecFx32 delta;
} ChildSlot;

typedef struct {
    u8 pad_00[0xb8];
    VecFx32 position;
} OwnerEntry;

typedef struct {
    u8 pad_00[0xc];
    OwnerEntry *entry;
    u8 pad_10[0x28];
    u8 actorId;
    u8 pad_39[0x23];
    ChildLayout *layouts;
    u8 pad_60[0x8];
    ChildSlot children[24];
} ChildOwner;

typedef struct {
    u32 flags;
    u8 node[0x20];
    u32 drawFlags;
} FieldActor;

extern FieldActor *func_02036240(u32 actorId);
extern void SceneNode_Draw_01ffb12c(void *node);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);

void DrawChildSpawner_020a0a08(ChildOwner *owner)
{
    FieldActor *actor = func_02036240(owner->actorId);
    VecFx32 base;
    VecFx32 position;
    VecFx32 previous;
    int i;

    actor->drawFlags |= 1;
    if (!(actor->flags & 0x20)) {
        SceneNode_Draw_01ffb12c(actor->node);
    }
    actor->drawFlags &= ~1;
    base = owner->entry->position;
    for (i = 0; i < 24; i++) {
        ChildSlot *slot = &owner->children[i];

        position = owner->layouts[slot->layoutIndex].offset;
        VEC_Add_01ff9e0c(&position, &base, &position);
        previous = slot->object->position;
        Obj_SetPosition_0203569c(slot->object->base, &position);
        VEC_Subtract_01ff9e3c(&position, &previous, &slot->delta);
    }
}
