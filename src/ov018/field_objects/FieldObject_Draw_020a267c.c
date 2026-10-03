#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SceneNode {
    u16 flags;
    u8 pad_02[0x76];
    void *model;
    u8 pad_7c[4];
    MtxFx33 rotation;
    VecFx32 translation;
    u8 pad_b0[0x54];
} SceneNode;

typedef struct ObjectDef {
    u8 pad_00[0x60];
    SceneNode nodes[4];
} ObjectDef;

typedef struct CollisionShape {
    u8 *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef void (*ComputeBoundsFunc)(CollisionShape *shape, s32 *bounds);

typedef struct Actor {
    u8 pad_000[0x130];
    CollisionShape shape;
    VecFx32 delta;
    s32 sweptBounds[6];
} Actor;

typedef struct Basis {
    VecFx32 x;
    VecFx32 y;
    VecFx32 z;
} Basis;

typedef struct FieldObject {
    u8 pad_00[4];
    ObjectDef *def;
    u8 pad_08[0x2a];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[4];
    SceneNode *anim;
    u8 pad_4c[4];
    u16 flags;
    s8 state;
    u8 pad_53;
    s32 hurtTimer;
    u8 pad_58[0x18];
    VecFx32 forward;
    VecFx32 up;
    u8 pad_88[0x18];
    s32 kind;
} FieldObject;

extern ComputeBoundsFunc data_020559c0[];

extern Actor *func_02036240(u32 id);
extern void BuildBasisFromForward_0204bf70(const VecFx32 *forward, const VecFx32 *up, Basis *basis);
extern void MTX_Identity33_01ff90ec(MtxFx33 *mtx);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void UpdateBoxAxisAlignedFlag_0203b1c0(void *data);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void Model_SetAllMaterialAlpha_0201a900(void *model, int alpha);
extern void SceneNode_Draw_01ffb12c(SceneNode *node);
extern fx32 func_ov031_020bc700(void);
extern void func_01fff9a0(SceneNode *node, fx32 scale, MtxFx33 *rotation, int alpha, int flags);

static inline void ComputeBounds(CollisionShape *shape)
{
    data_020559c0[shape->kind](shape, (s32 *)((u8 *)shape + 4));
}

void FieldObject_Draw_020a267c(FieldObject *obj)
{
    Actor *actor = func_02036240(obj->actorId);
    SceneNode *node;
    MtxFx33 rotation;
    Basis built;
    Basis basis;
    MtxFx33 identity;
    fx32 height;
    int alpha;

    if (obj->flags & 8) {
        return;
    }
    if (obj->flags & 0x800) {
        return;
    }
    switch (obj->kind) {
    case 3:
        node = &obj->def->nodes[0];
        break;
    case 1:
        node = &obj->def->nodes[1];
        break;
    case 10:
        node = &obj->def->nodes[2];
        break;
    case 2:
        node = &obj->def->nodes[3];
        break;
    }
    node->translation = obj->position;
    if (obj->flags & 0x400) {
        BuildBasisFromForward_0204bf70(&obj->forward, &obj->up, &built);
        basis = built;
        rotation = *(MtxFx33 *)&basis;
        obj->up = *(VecFx32 *)rotation.m[1];
        node->rotation = rotation;
        node->flags &= ~0x20;
        *(MtxFx33 *)(actor->shape.data + 0x18) = rotation;
        ComputeBounds(&actor->shape);
        OffsetBoxByDelta_0203ac70(actor->shape.bounds, actor->sweptBounds, &actor->delta);
        UpdateBoxAxisAlignedFlag_0203b1c0(actor->shape.data);
        VEC_MultAdd_01ffa09c(-0x800, &obj->up, (VecFx32 *)actor->shape.data, &obj->position);
    } else {
        MTX_Identity33_01ff90ec(&identity);
        node->rotation = identity;
        node->flags &= ~0x20;
    }
    if (obj->hurtTimer != 0 && obj->state == 0) {
        Model_SetAllMaterialAlpha_0201a900(node->model, 12);
        SceneNode_Draw_01ffb12c(node);
        Model_SetAllMaterialAlpha_0201a900(node->model, 31);
        return;
    }
    if (obj->flags & 0x20) {
        SceneNode_Draw_01ffb12c(obj->anim);
    }
    if (obj->state == 0) {
        height = obj->position.z + 0x800 + func_ov031_020bc700();
        if (height >= 0x10) {
            if (height < 0x1800) {
                alpha = height * 31 / 0x1800;
                if (alpha == 0) {
                    return;
                }
            } else {
                alpha = 31;
            }
            func_01fff9a0(node, 0x1000, &node->rotation, alpha, 1);
        }
    }
}
