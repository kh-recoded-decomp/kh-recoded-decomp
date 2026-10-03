#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 active : 1;
    u8 airborne : 1;
    u8 flagsHigh : 6;
    u8 phase;
    u16 timer;
    VecFx32 origin;
    VecFx32 velocity;
    fx32 scale;
    int angle;
} LaunchMotion;

typedef struct {
    u8 pad_00[0x90];
    s8 alphaTable[1];
} WanderDef;

typedef struct {
    u8 pad_00[0x14];
    u16 nodeFlags;
    u8 pad_16[0x12];
    void *anim;
    u8 pad_2c[0x8];
    u8 renderObj[0x58];
    void *model;
    s16 rotY;
    u8 pad_92[0x26];
    VecFx32 position;
    VecFx32 scale;
} WanderRender;

typedef struct {
    u8 pad_00[0x8];
    WanderDef *def;
    WanderRender *render;
    u8 pad_10[0x54];
    LaunchMotion motion[2];
    u8 pad_ac[0x7];
    s8 alphaIndex;
} WanderObject;

extern s8 func_ov040_020bd9fc(VecFx32 *position);
extern void RemoveAnimationFromRenderObject_02018850(void *renderObj, void *anim);
extern void AttachAnimationToRenderObject_0201875c(void *renderObj, void *anim);
extern int GetMaterialAlpha_0201a810(void *model, int material);
extern int GetMaterialPolygonId_0201a7a0(void *model, int material);
extern void Model_SetAllMaterialAlpha_0201a900(void *model, int alpha);
extern void Model_SetAllPolygonIds_0201a8c0(void *model, int polygonId);
extern void SceneNode_Draw_01ffb12c(void *node);

void DrawWanderMotionModels_020a15a8(WanderObject *object)
{
    WanderRender *render = object->render;
    WanderDef *def = object->def;
    int i;
    LaunchMotion *motion;
    int alpha;
    int polygonId;

    for (i = 1; i >= 0; i--) {
        motion = &object->motion[i];

        if (!motion->airborne) {
            continue;
        }
        if (object->alphaIndex < 0) {
            VecFx32 probe = motion->origin;
            probe.y += 0x800;
            object->alphaIndex = func_ov040_020bd9fc(&probe);
        }
        render->position = motion->origin;
        render->scale.x = render->scale.y = render->scale.z = motion->scale;
        render->rotY = motion->angle;
        render->nodeFlags |= 0x20;
        if (object->alphaIndex >= 0 && def->alphaTable[object->alphaIndex] < 0x1f) {
            if (render->anim != NULL) {
                RemoveAnimationFromRenderObject_02018850(render->renderObj, render->anim);
            }
            alpha = GetMaterialAlpha_0201a810(render->model, 0);
            polygonId = GetMaterialPolygonId_0201a7a0(render->model, 0);
            Model_SetAllMaterialAlpha_0201a900(render->model, def->alphaTable[object->alphaIndex]);
            Model_SetAllPolygonIds_0201a8c0(render->model, 8);
        }
        SceneNode_Draw_01ffb12c(&render->nodeFlags);
        if (object->alphaIndex >= 0 && def->alphaTable[object->alphaIndex] < 0x1f) {
            Model_SetAllMaterialAlpha_0201a900(render->model, alpha);
            Model_SetAllPolygonIds_0201a8c0(render->model, polygonId);
            if (render->anim != NULL) {
                AttachAnimationToRenderObject_0201875c(render->renderObj, render->anim);
            }
        }
    }
}
