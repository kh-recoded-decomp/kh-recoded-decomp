#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactHandler {
    void *func;
    void *context;
} ContactHandler;

typedef struct ActorNode {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x80 - 0x06];
    u16 animTimer;
    u8 pad_82[0x10c - 0x82];
    u8 collision[0x80];
    ContactHandler contact;
} ActorNode;

typedef struct LinkEffect {
    u16 flags;
    u8 pad_02[0x7c - 0x02];
    u16 timer;
    u8 pad_7e[0xa4 - 0x7e];
    VecFx32 position;
} LinkEffect;

typedef struct LinkOwner {
    u8 pad_00[0x59];
    u8 listId;
    u8 pad_5a[0x68 - 0x5a];
    LinkEffect *effect;
} LinkOwner;

typedef struct ShapeInfo {
    u8 data[0x14];
} ShapeInfo;

typedef struct Actor {
    u8 pad_00[4];
    LinkOwner *owner;
    void *entity;
    u8 pad_0c[0x30 - 0x0c];
    u16 renderFlags;
    u8 actorId;
    u8 slotIndex;
    u8 pad_34[4];
    VecFx32 position;
    u8 pad_44[3];
    s8 animIndex;
    LinkEffect *effect;
    u8 pad_4c[6];
    u8 kind;
    u8 pad_53[7];
    u16 flags;
} Actor;

extern BOOL IsDestroyed_020a31f8(Actor *self);
extern void CacheEntry_SetActive_02087258(Actor *self, int active);
extern void func_ov001_0208078c(void *entity, u8 listId, u8 slotIndex, u8 actorId, ShapeInfo *info, int kind,
                                fx32 sizeX, fx32 sizeY, fx32 sizeZ, int angle, int allocate, int mode);
extern void func_020358b0(u8 actorId, u16 *counter, int arg, int mode);
extern ActorNode *func_02036240(u8 actorId);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern void func_0202f4d8(void *anim);
extern void Obj_SetPosition_0203569c(ActorNode *node, const VecFx32 *position);
extern void func_020359f8(u8 actorId, int a1, int a2);
extern void func_020369c8(u8 actorId, Actor *self, int mode);
extern void func_02034050(void *collision, int mode, int flags);
extern BOOL IsNodeFlagBitClear_020872b8(Actor *self);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_0202ed9c(void *object, u16 *counter, int arg, int mode);
extern void ResizeBoxCollisionObject_02033e6c(void *object, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle);
extern void func_ov001_0207f050(int mode);
extern void FieldObject_HandlePushContact_020a1f38(void);

static inline ContactHandler MakeHandler(void *func, void *context)
{
    ContactHandler handler;
    handler.func = func;
    handler.context = context;
    return handler;
}

void HandleLinkEvent_020a2418(Actor *self, int event, u16 *counter, int arg)
{
    LinkOwner *owner = self->owner;
    ActorNode *node;
    BOOL enable;
    LinkEffect *effect;
    ShapeInfo info;

    if ((event == 0 && !(self->flags & 0x600)) || (event == 1 && (self->flags & 0x200)) ||
        (event == 10 && (self->flags & 0x400))) {
        if (IsDestroyed_020a31f8(self)) {
            return;
        }
        CacheEntry_SetActive_02087258(self, 1);
        func_ov001_0208078c(self->entity, self->owner->listId, self->slotIndex, self->actorId, &info, 3, 0x1800,
                            0x1800, 0x1800, 0, 1, 0);
        func_020358b0(self->actorId, counter, arg, 4);
        (*counter)++;
        node = func_02036240(self->actorId);
        RebindAnimTracks_020809d0(&node->animFlags, self->animIndex, 0);
        func_0202f4e8(&node->animFlags);
        Obj_SetPosition_0203569c(node, &self->position);
        if (!(node->flags & 0x20)) {
            node->animTimer = 0;
            node->animFlags |= 0x20;
        }
        func_020359f8(self->actorId, 0, 0);
        func_020369c8(self->actorId, self, 0xc);
        enable = TRUE;
        func_02034050(node->collision, 1, 4);
        if (IsDestroyed_020a31f8(self) || !IsNodeFlagBitClear_020872b8(self)) {
            enable = FALSE;
        }
        ActorSlot_SetFlag8ByIndex_02036120(self->actorId, enable);
        self->flags |= 0x40;
        func_02034050(node->collision, 3, 0xc);
        self->renderFlags |= 4;
        if (!(self->flags & 0x100)) {
            if (self->flags & 0x400) {
                self->kind = 10;
            } else if (self->flags & 0x200) {
                self->kind = 1;
            } else {
                self->kind = 0;
            }
        }
    } else if ((event == 2 && !(self->flags & 0x800)) || (event == 3 && (self->flags & 0x800))) {
        if (!(self->flags & 0x100) || IsDestroyed_020a31f8(self)) {
            return;
        }
        CacheEntry_SetActive_02087258(self, 1);
        node = func_02036240(self->actorId);
        self->effect = NNSi_FndAllocFromDefaultHeap_0202a178(0x104);
        func_0202ed9c(self->effect, counter, arg, 4);
        if (!(self->flags & 0x80)) {
            self->animIndex = 0;
            RebindAnimTracks_020809d0(self->effect, self->animIndex, 0);
            func_0202f4d8(self->effect);
        } else {
            self->animIndex = 1;
            RebindAnimTracks_020809d0(&node->animFlags, self->animIndex, 0);
            func_0202f4e8(&node->animFlags);
        }
        self->effect->position = self->position;
        effect = self->effect;
        effect->timer = 0;
        effect->flags |= 0x20;
        (*counter)++;
        if (self->flags & 0x800) {
            node->contact = MakeHandler(FieldObject_HandlePushContact_020a1f38, self);
            self->kind = 3;
            ResizeBoxCollisionObject_02033e6c(node->collision, 0x1333, 0x1800, 0x1333, 0);
            Obj_SetPosition_0203569c(node, &self->position);
        } else {
            self->kind = 2;
        }
        func_02034050(node->collision, 3, 0xc);
        func_ov001_0207f050(0xc);
        self->flags |= 0x100;
    } else if (event == 8 && !IsDestroyed_020a31f8(self) && owner->effect == NULL) {
        owner->effect = NNSi_FndAllocFromDefaultHeap_0202a178(0x104);
        func_0202ed9c(owner->effect, counter, arg, 4);
        RebindAnimTracks_020809d0(owner->effect, 0, 0);
        func_0202f4d8(owner->effect);
        (*counter)++;
    }
}
