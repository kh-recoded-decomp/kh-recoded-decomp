#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ModelNode {
    u16 flags;
    u8 pad_02[0x12];
    void *animObj;
    u8 pad_18[8];
    u8 renderObj[0x58];
    void *model;
    u8 pad_7c[0x28];
    VecFx32 translation;
} ModelNode;

typedef struct Owner {
    u8 pad_00[0x68];
    ModelNode *node;
} Owner;

typedef struct Entity {
    u32 flags;
    ModelNode node;
} Entity;

typedef struct Actor {
    u8 pad_00[4];
    Owner *owner;
    u8 pad_08[0x2a];
    u8 entityId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[3];
    s8 shadowDisabled;
    ModelNode *modelNode;
    u8 pad_4c[3];
    u8 state : 3;
    u8 counter : 3;
    u8 pad_4f_6 : 2;
    s8 alpha;
    u8 pad_51[5];
    s16 angle;
    u8 pad_58[2];
    u16 flags;
} Actor;

extern u32 func_ov035_020bae74(void);
extern void func_ov001_02080a10(ModelNode *node, u32 value);
extern void SceneNode_Draw_01ffb12c(ModelNode *node);
extern Entity *func_02036240(u32 id);
extern void RemoveAnimationFromRenderObject_02018850(void *renderObj, void *animObj);
extern void AttachAnimationToRenderObject_0201875c(void *renderObj, void *animObj);
extern u32 GetMaterialAlpha_0201a810(void *model, u32 materialIndex);
extern u32 GetMaterialPolygonId_0201a7a0(void *model, u32 materialIndex);
extern void Model_SetAllMaterialAlpha_0201a900(void *model, int alpha);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, int polygonId);
extern void MTX_Identity33_01ff90ec(MtxFx33 *mtx);
extern void func_01fff9a0(ModelNode *node, fx32 size, MtxFx33 *rotation, int alpha, int mode);

void DrawActorModel_020a2c4c(Actor *actor)
{
    Owner *owner = actor->owner;
    ModelNode *node;

    if (func_ov035_020bae74() != 0) {
        return;
    }
    if (actor->state == 2 || actor->alpha <= 0) {
        return;
    }
    if (actor->flags & 0x20) {
        owner->node->translation = actor->position;
        func_ov001_02080a10(owner->node, actor->angle << 12);
        SceneNode_Draw_01ffb12c(owner->node);
    }
    if (!(actor->flags & 0x40)) {
        return;
    }
    if ((actor->flags & 0x100) && !(actor->flags & 0x80)) {
        node = actor->modelNode;
    } else {
        node = &func_02036240(actor->entityId)->node;
    }
    if (actor->alpha < 31) {
        u32 savedAlpha;
        u32 savedPolygonId;
        if (node->animObj != NULL) {
            RemoveAnimationFromRenderObject_02018850(node->renderObj, node->animObj);
        }
        savedAlpha = GetMaterialAlpha_0201a810(node->model, 0);
        savedPolygonId = GetMaterialPolygonId_0201a7a0(node->model, 0);
        Model_SetAllMaterialAlpha_0201a900(node->model, actor->alpha);
        Model_SetAllPolygonIds_0201a8c0(node->model, 7);
        SceneNode_Draw_01ffb12c(node);
        Model_SetAllMaterialAlpha_0201a900(node->model, savedAlpha);
        Model_SetAllPolygonIds_0201a8c0(node->model, savedPolygonId);
        if (node->animObj != NULL) {
            AttachAnimationToRenderObject_0201875c(node->renderObj, node->animObj);
        }
    } else if (actor->shadowDisabled == 0 && (node->flags & 2)) {
        MtxFx33 identity;
        MtxFx33 rotation;
        MTX_Identity33_01ff90ec(&identity);
        rotation = identity;
        func_01fff9a0(node, 0x1800, &rotation, 0x1f, 1);
    } else {
        SceneNode_Draw_01ffb12c(node);
    }
}
