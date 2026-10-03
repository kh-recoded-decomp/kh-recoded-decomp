#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Owner {
    u8 pad_00[0x68];
    void *resource;
} Owner;

typedef struct ActorNode {
    u8 pad_00[4];
    u8 anim[4];
} ActorNode;

typedef struct Actor {
    u8 pad_00[4];
    Owner *owner;
    u8 *entity;
    u8 pad_0c[0x32 - 0x0c];
    u8 actorId;
    u8 pad_33[0x4f - 0x33];
    u8 state : 3;
    u8 stateHigh : 5;
    u8 pad_50[6];
    s16 frame;
    u8 pad_58[2];
    u16 flags;
} Actor;

extern int func_0202f4b8(void *resource, int index);
extern ActorNode *func_02036240(u8 actorId);
extern u16 AdvanceAnimationTracks_0202ef24(void *state, fx32 delta);
extern void Obj_RemoveFromQuadTree_020355f4(void *entity);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);

BOOL UpdateDespawnAnimation_020a2e08(Actor *self)
{
    Owner *owner = self->owner;
    if (self->flags & 0x20) {
        self->frame++;
        if (func_0202f4b8(owner->resource, 0) <= (self->frame + 1) << 12) {
            self->flags &= ~0x20;
        }
    }
    if (self->flags & 0x10) {
        if (AdvanceAnimationTracks_0202ef24(func_02036240(self->actorId)->anim, 0x1000)) {
            self->flags &= ~0x50;
        }
    }
    if (!(self->flags & 0x30)) {
        self->state = 2;
        Obj_RemoveFromQuadTree_020355f4(self->entity + 0x10);
        ActorSlot_SetFlag8ByIndex_02036120(self->actorId, FALSE);
    }
    return FALSE;
}
