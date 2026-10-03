#include "nitro/types.h"

typedef struct ActorNode {
    u8 pad_00[4];
    s16 anim;
} ActorNode;

typedef struct Actor {
    u8 pad_00[0x30];
    u16 renderFlags;
    u8 actorId;
    u8 pad_33[0x47 - 0x33];
    s8 animIndex;
    u8 pad_48[0x5a - 0x48];
    u16 flags;
} Actor;

extern ActorNode *func_02036240(u8 actorId);
extern void func_0202f4d8(s16 *anim);
extern void RebindAnimTracks_020809d0(s16 *anim, int blendIndex, int frame);
extern void SettleLinkHeight_020a2250(Actor *self, BOOL sweep);
extern void RefreshLeadLinkFlags_020a21e0(Actor *actor);

void ResetLinkAnimation_020a23b0(Actor *self)
{
    self->flags &= 0xfe6f;
    self->animIndex = 0;
    RebindAnimTracks_020809d0(&func_02036240(self->actorId)->anim, self->animIndex, 0);
    func_0202f4d8(&func_02036240(self->actorId)->anim);
    self->renderFlags |= 8;
    if (!(self->flags & 1)) {
        SettleLinkHeight_020a2250(self, TRUE);
    }
    RefreshLeadLinkFlags_020a21e0(self);
}
