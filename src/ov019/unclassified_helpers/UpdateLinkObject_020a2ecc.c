#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

enum { LINK_NONE, LINK_PRESENT };

typedef struct VelocityPair {
    s32 speed;
    s32 accel;
} VelocityPair;

typedef struct ActorNode {
    u32 flags;
    u8 anim[0xa0];
    VecFx32 position;
    u8 pad_b0[0x5c];
    u8 collision[0x80];
    VelocityPair velocity;
} ActorNode;

typedef struct Actor {
    u8 pad_00[0x10];
    CollisionShape shape;
    u8 pad_30[2];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[3];
    s8 animIndex;
    ActorNode *linkedNode;
    u8 pad_4c[3];
    u8 state : 3;
    u8 stateMid : 3;
    u8 isLead : 1;
    u8 stateHigh : 1;
    s8 alpha;
    u8 threshold;
    u8 hasLinks;
    s8 callbackId;
    s8 cooldown;
    u8 pad_55[5];
    u16 flags;
    u8 pad_5c[8];
    fx32 groundY;
    fx32 dropDelta;
} Actor;

extern ActorNode *func_02036240(u8 actorId);
extern u16 AdvanceAnimationTracks_0202ef24(void *state, fx32 delta);
extern void ResetLinkAnimation_020a23b0(Actor *self);
extern int func_ov035_020bae64(void);
extern u8 GetMovieEntryKind_020badf0(int index);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern void ResizeBoxCollisionObject_02033e6c(void *object, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle);
extern void Obj_SetPosition_0203569c(ActorNode *entity, const VecFx32 *position);
extern void BuildCollisionShape_02080834(CollisionShape *shape, const VecFx32 *position, int kind, fx32 sizeX,
                                         fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int unused);
extern BOOL UpdateDespawnAnimation_020a2e08(Actor *self);

static inline BOOL IsCallbackReady(Actor *self)
{
    s8 callbackId = self->callbackId;
    if (callbackId == func_ov035_020bae64()) {
        return GetMovieEntryKind_020badf0(callbackId) <= self->threshold;
    }
    return FALSE;
}

BOOL UpdateLinkObject_020a2ecc(Actor *self)
{
    ActorNode *node;
    fx32 oldY;
    VelocityPair stopped;
    u16 flags = self->flags;

    if (flags & 2) {
        return FALSE;
    }
    if (flags & 0x1000) {
        self->alpha += 4;
        if (self->alpha >= 0x1f) {
            self->alpha = 0x1f;
            self->flags = flags & 0xEFFF;
        }
    } else if (flags & 0x2000) {
        self->alpha -= 4;
        if (self->alpha <= 0) {
            self->alpha = 0;
            self->flags = flags & 0xDFFF;
        }
    }
    if (self->flags & 0x80) {
        if (AdvanceAnimationTracks_0202ef24(func_02036240(self->actorId)->anim, 0x1000)) {
            ResetLinkAnimation_020a23b0(self);
        } else {
            return FALSE;
        }
    }
    if (self->state == 0 && (self->flags & 0x100) && IsCallbackReady(self)) {
        node = func_02036240(self->actorId);
        self->flags |= 0x80;
        self->animIndex = 1;
        RebindAnimTracks_020809d0(node->anim, self->animIndex, 0);
        func_0202f4e8(node->anim);
        if (self->flags & 0x800) {
            stopped.speed = 0;
            stopped.accel = 0;
            node->velocity = stopped;
            ResizeBoxCollisionObject_02033e6c(node->collision, 0x1800, 0x1800, 0x1800, 0);
            Obj_SetPosition_0203569c(node, &self->position);
        }
        self->hasLinks = (self->flags & 0x600) == 0 ? LINK_NONE : LINK_PRESENT;
    }
    if (self->stateMid != 0) {
        self->stateMid--;
    }
    self->dropDelta = 0;
    if (self->cooldown > 0) {
        self->cooldown--;
    }
    if (self->flags & 1) {
        oldY = self->position.y;
        self->position.y = oldY - 0x600;
        if (self->position.y <= self->groundY) {
            self->position.y = self->groundY;
            self->flags &= 0xFFFE;
            BuildCollisionShape_02080834(&self->shape, &self->position, 3, 0x1800, 0x1800, 0x1800, 0, 0, -1);
            self->stateMid = 4;
        }
        Obj_SetPosition_0203569c(func_02036240(self->actorId), &self->position);
        if (self->flags & 0x100) {
            self->linkedNode->position = self->position;
        }
        self->dropDelta = oldY - self->position.y;
    }
    if (self->state == 1) {
        return UpdateDespawnAnimation_020a2e08(self);
    }
    return FALSE;
}
