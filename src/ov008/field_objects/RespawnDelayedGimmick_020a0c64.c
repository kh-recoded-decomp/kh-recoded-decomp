#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct FieldObjectDef {
    u8 pad_00[0x54];
    s32 recordParamA;
    s32 recordParamB;
    u8 pad_5c[0x14];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
} FieldObjectDef;

typedef struct Gimmick {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    void *entry;
    u8 pad_10[0x4];
    int (*update)(struct Gimmick *gimmick);
    u8 pad_18[0x20];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[0x05];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u8 pad_50[0x03];
    s8 blendIndex;
    u8 pad_54[0x4];
    int phase;
    fx32 delay;
    fx32 timer;
} Gimmick;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7a];
    u16 angle;
} FieldActor;

extern BOOL SpawnFieldActor_0208078c(void *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern FieldActor *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(FieldActor *entity, const VecFx32 *position);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern BOOL IsObjectFlagClear_0207f7a4(Gimmick *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_020359f8(int index, int a1, int a2);
extern int Gimmick_WaitOpenDelay_020a0d8c(Gimmick *gimmick);

void RespawnDelayedGimmick_020a0c64(Gimmick *gimmick)
{
    FieldObjectDef *def = gimmick->def;
    ShapeParams shape;
    FieldActor *actor;
    u16 angle;

    SpawnFieldActor_0208078c(gimmick->entry, gimmick->group, gimmick->index, gimmick->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, gimmick->angle, !(gimmick->stateFlags & 8), TRUE);
    func_020358b0(gimmick->actorId, def->recordParamA, def->recordParamB, 3);
    actor = func_02036240(gimmick->actorId);
    Obj_SetPosition_0203569c(actor, &gimmick->position);
    angle = gimmick->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    gimmick->update = Gimmick_WaitOpenDelay_020a0d8c;
    gimmick->phase = 0;
    gimmick->timer = -gimmick->delay;
    RebindAnimTracks_020809d0(&actor->animFlags, gimmick->blendIndex, 0);
    func_0202f4e8(&actor->animFlags);
    if (IsObjectFlagClear_0207f7a4(gimmick)) {
        func_020359f8(gimmick->actorId, 0, 0);
        ActorSlot_SetFlag8ByIndex_02036120(gimmick->actorId, FALSE);
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(gimmick->actorId, FALSE);
    }
}
