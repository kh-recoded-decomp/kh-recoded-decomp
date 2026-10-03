#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct HitInfo {
    u8 pad_00[0xc];
    u8 kind;
} HitInfo;

typedef struct VelocityPair {
    s32 speed;
    s32 accel;
} VelocityPair;

typedef struct ActorNode {
    u8 pad_000[4];
    u8 anim[0x188];
    VelocityPair velocity;
} ActorNode;

typedef struct DropRequest {
    u8 data[0x18];
} DropRequest;

typedef struct Actor {
    u8 pad_00[0x30];
    u16 renderFlags;
    u8 actorId;
    u8 slotIndex;
    u8 pad_34[4];
    VecFx32 position;
    u16 linkId;
    u8 linkSlot;
    s8 animIndex;
    u8 pad_48[4];
    s8 sizeX;
    s8 sizeY;
    s8 phase;
    u8 state : 3;
    u8 stateMid : 3;
    u8 isLead : 1;
    u8 stateHigh : 1;
    u8 counter;
    u8 linkIndex;
    u8 kind;
    s8 callbackId;
    u8 pad_54[6];
    u16 flags;
} Actor;

extern BOOL func_ov001_0208764c(void);
extern ActorNode *func_02036240(u8 actorId);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern Actor *FindLivePrevLink_020a2098(Actor *actor);
extern Actor *FindLiveNextLink_020a20e0(Actor *actor);
extern void NNS_FndInitListWithOffset0_020a23a0(Actor *link, Actor *source);
extern void _fp_init_020a23ac(Actor *link, Actor *source);
extern void DropRequest_InitKind0_020874fc(DropRequest *request, int dropIndex, int variant, u32 saveGroup,
                                           u32 saveIndex);
extern void DropRequest_InitKind1_020874e0(DropRequest *request, int dropIndex, int variant, u32 saveGroup,
                                           u32 saveIndex);
extern void GrantEntryUnlockReward_02087518(Actor *owner, DropRequest *request);
extern void RollRewardOrbDrop_020665bc(int dropIndex, VecFx32 *target);
extern void RefreshLeadLinkFlags_020a21e0(Actor *actor);
extern void SpawnSoundSlot_0204da8c(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern void EnterState12WithHalfRate_020bb1ac(int callbackId, int slot);
extern void AddSessionCounter_02063a80(int index, int amount);

int HandleLinkHit_020a2774(Actor *self, HitInfo *hit)
{
    BOOL locked;
    Actor *link;
    u16 flags;
    VelocityPair stopped;
    DropRequest request;

    if (func_ov001_0208764c()) {
        return 0x10;
    }
    if (hit != NULL && hit->kind == 0xff) {
        return 0x10;
    }
    locked = FALSE;
    if ((self->flags & 0x100) && !(self->flags & 0x800)) {
        locked = TRUE;
    }
    if (locked) {
        return 1;
    }
    if (hit != NULL && hit->kind == 10) {
        self->phase = 0;
    } else {
        self->phase--;
        self->stateMid = 4;
        if (self->phase > 0) {
            return 0;
        }
    }
    self->state = 1;
    if (!(self->flags & 0x200) || (self->flags & 0x800)) {
        self->flags |= 0x20;
    }
    self->animIndex = 1;
    RebindAnimTracks_020809d0(func_02036240(self->actorId)->anim, self->animIndex, 0);
    func_0202f4e8(func_02036240(self->actorId)->anim);
    self->flags |= 0x10;
    link = FindLivePrevLink_020a2098(self);
    if (link != NULL) {
        NNS_FndInitListWithOffset0_020a23a0(link, self);
    }
    link = FindLiveNextLink_020a20e0(self);
    if (link != NULL) {
        _fp_init_020a23ac(link, self);
    }
    self->flags |= 0x8000;
    self->renderFlags &= ~0x10;
    self->renderFlags &= ~8;
    if (self->flags & 0x100) {
        if (self->sizeX >= 0) {
            RollRewardOrbDrop_020665bc(self->sizeX, &self->position);
        }
    } else {
        if (self->flags & 0x400) {
            DropRequest_InitKind0_020874fc(&request, self->sizeY, self->sizeX, self->linkId, self->linkSlot);
            GrantEntryUnlockReward_02087518(self, &request);
        } else if (self->sizeY >= 0) {
            DropRequest_InitKind1_020874e0(&request, self->sizeY, self->sizeX, self->linkId, self->linkSlot);
            GrantEntryUnlockReward_02087518(self, &request);
        }
        if (self->sizeX >= 0) {
            RollRewardOrbDrop_020665bc(self->sizeX, &self->position);
        }
    }
    RefreshLeadLinkFlags_020a21e0(self);
    flags = self->flags;
    if ((flags & 0x100) && (!(flags & 0x100) || (flags & 0x800))) {
        stopped.speed = 0;
        stopped.accel = 0;
        func_02036240(self->actorId)->velocity = stopped;
    }
    SpawnSoundSlot_0204da8c(0, 0x2d, &self->position, 0);
    if (self->callbackId >= 0) {
        EnterState12WithHalfRate_020bb1ac(self->callbackId, self->slotIndex);
    }
    AddSessionCounter_02063a80(0x1c, 1);
    return 0;
}
