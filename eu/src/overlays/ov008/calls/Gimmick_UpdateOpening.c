#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CollisionShape {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct {
    VecFx32 axes[3];
} Basis;

typedef struct AnimModel {
    u16 nodeFlags;
    u8 pad_02[0x7e];
    Basis rotation;
    u8 pad_a4[0x34];
    u8 blendTable[0x10];
} AnimModel;

typedef struct GimmickWork {
    u8 pad_00[0x14];
    AnimModel model;
} GimmickWork;

typedef struct Gimmick {
    u8 pad_00[0xC];
    GimmickWork *work;
    u8 pad_10[0x28];
    u8 actorId;
    u8 pad_39[0x7];
    VecFx32 position;
    u8 pad_4c[0xc];
    int phase;
    fx32 delay;
    fx32 timer;
    fx32 duration;
    fx32 speed;
    VecFx32 direction;
} Gimmick;

extern int Anim_GetFrame(AnimModel *model, int track);
extern int func_0202f4cc(AnimModel *model, int track);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void InitCylinderShape(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end, const VecFx32 *direction, fx32 length, fx32 radius);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision(CollisionQuery *query);
extern void BuildBasisFromForward(const VecFx32 *forward, const VecFx32 *up, Basis *basis);
extern int Gimmick_WaitOpenDelay(Gimmick *gimmick);
extern void IsOwnerStatusActive(void);
extern void ApplyScaledVelocityToPlayer(void);

static inline void Gimmick_SetBlend(Gimmick *gimmick, u16 trackIndex, s16 blendIndex)
{
    AnimModel *model = &gimmick->work->model;

    selectJointAnimationBlend(model, trackIndex, model->blendTable, blendIndex);
}

int Gimmick_UpdateOpening(Gimmick *gimmick)
{
    QueryWorkspace workspace;
    CollisionQuery sweep;
    CollisionQuery query;
    CollisionCylinder cylinder;
    CollisionShape shape;
    VecFx32 end;
    VecFx32 up;
    VecFx32 endResult;
    CollisionShape shapeResult;
    VecFx32 delta;
    VecFx32 direction;
    VecFx32 upResult;
    Basis basis;
    QueryCallback filter;
    QueryCallback callback;
    AnimModel *model;
    int frame;

    switch (gimmick->phase) {
    case 2:
        gimmick->speed += 0x1800;
        if (gimmick->speed >= 0x34cd) {
            gimmick->speed = 0x34cd;
        }
        frame = Anim_GetFrame(&gimmick->work->model, 0);
        if (frame + 0x1000 >= func_0202f4cc(&gimmick->work->model, 0)) {
            gimmick->phase = 3;
            Gimmick_SetBlend(gimmick, 0, 2);
            Gimmick_SetBlend(gimmick, 2, 2);
            Gimmick_SetBlend(gimmick, 4, 2);
        }
        break;
    case 3:
        gimmick->timer += 0x1000;
        if (gimmick->timer >= 0x3c000) {
            frame = Anim_GetFrame(&gimmick->work->model, 0);
            if (frame + 0x1000 >= func_0202f4cc(&gimmick->work->model, 0)) {
                gimmick->phase = 4;
                Gimmick_SetBlend(gimmick, 0, 3);
                Gimmick_SetBlend(gimmick, 2, 3);
                Gimmick_SetBlend(gimmick, 4, 3);
            }
        }
        break;
    case 4:
        gimmick->speed -= 0x666;
        if (gimmick->speed <= 0) {
            gimmick->speed = 0;
        }
        frame = Anim_GetFrame(&gimmick->work->model, 0);
        if (frame + 0x1000 >= func_0202f4cc(&gimmick->work->model, 0)) {
            gimmick->timer = 0;
            gimmick->phase = 0;
            ActorSlot_SetFlag8ByIndex(gimmick->actorId, FALSE);
            return (int)Gimmick_WaitOpenDelay;
        }
        break;
    }
    if (gimmick->speed != 0) {
        VEC_MultAdd(gimmick->speed, &gimmick->direction, &gimmick->position, &endResult);
        end = endResult;
        VEC_Subtract(&end, &gimmick->position, &delta);
        direction = delta;
        InitCylinderShape(&shapeResult, &cylinder, &gimmick->position, &end, &direction, func_01ffaff4(&direction, &direction), 0xcd);
        shape = shapeResult;
        CollisionQuery_Init(&query, 0, NULL, 8, 2, 0, &shape, &workspace, NULL);
        sweep = query;
        filter.func = IsOwnerStatusActive;
        filter.arg = NULL;
        sweep.filter = filter;
        callback.func = ApplyScaledVelocityToPlayer;
        callback.arg = gimmick;
        sweep.callback = callback;
        SweepWorldCollision(&sweep);
    }
    upResult.x = 0;
    upResult.y = 0x1000;
    upResult.z = 0;
    up = upResult;
    BuildBasisFromForward(&gimmick->direction, &up, &basis);
    model = &gimmick->work->model;
    model->rotation = basis;
    model->nodeFlags &= ~0x20;
    return 0;
}