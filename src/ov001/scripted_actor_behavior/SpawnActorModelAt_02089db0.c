#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
    u8 pad_82[0xf2];
    u8 savedState[8];
} ModelActor;

typedef struct {
    ModelActor *actor;
    u8 pad_04[0x36];
    u16 frame;
} ModelHolder;

typedef struct {
    u8 pad_000[0xd18];
    ModelHolder *holder;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 busy;
    u32 currentAngle;
    u32 targetAngle;
} ModelOwner;

extern const VecFx32 data_02053438;
extern void *func_02036230(void);
extern ModelActor *func_02036240(u32 actorId);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void func_02038a90(ModelHolder *holder, ModelActor *actor);
extern int ProjectPositionDownward_020352e0(void *map, int ground, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void Obj_SetPosition_0203569c(ModelActor *actor, const VecFx32 *position);
extern void ActorObject_Reset_02089cac(ModelOwner *owner, s32 actorId);

void SpawnActorModelAt_02089db0(ModelOwner *owner, int ground, const VecFx32 *offset, u32 actorId)
{
    VecFx32 position = data_02053438;
    void *map = func_02036230();
    ModelActor *actor = func_02036240((u16)actorId);
    u8 saved[8];
    ModelActor *model;
    u16 angle;

    if (owner->busy == 0) {
        if (owner->holder == 0) {
            owner->holder = NNSi_FndAllocFromDefaultHeap_0202a178(0x464);
            func_01ff8830(owner->holder, 0, 0x464);
        }
        func_01ff89a8(actor->savedState, saved, sizeof(saved));
        func_02038a90(owner->holder, actor);
        owner->holder->frame = 0;
        func_01ff89a8(saved, actor->savedState, sizeof(saved));
        if (ground != 0) {
            ProjectPositionDownward_020352e0(map, ground, &position);
        }
        VEC_Add_01ff9e0c(&position, offset, &position);
        Obj_SetPosition_0203569c(owner->holder->actor, &position);
        angle = owner->holder->actor->angle;
        owner->targetAngle = angle;
        owner->currentAngle = angle;
        model = owner->holder->actor;
        if (!(model->flags & 0x20)) {
            model->angle = angle;
            model->animFlags |= 0x20;
        }
        ActorObject_Reset_02089cac(owner, actorId);
    }
}
