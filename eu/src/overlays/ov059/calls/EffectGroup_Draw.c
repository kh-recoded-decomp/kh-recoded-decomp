#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct GroupModel {
    u16 flags;
    u8 pad_02[0x78 - 2];
    void *resModel;
    u8 pad_7c[4];
    MtxFx33 rotation;
    VecFx32 position;
    VecFx32 scale;
    u8 pad_bc[0x104 - 0xbc];
} GroupModel;

typedef struct EffectParams {
    s32 kind;
    VecFx32 axis;
} EffectParams;

typedef struct EffectSlot {
    u8 pad_000[2];
    s8 owner;
    u8 pad_003[0x24 - 3];
    VecFx32 velocity;
    GroupModel model;
    u8 pad_134[0x150 - 0x134];
    EffectParams *params;
} EffectSlot;

typedef struct TrailSlot {
    s32 frame;
    s32 modelIndex;
    VecFx32 position;
} TrailSlot;

typedef struct EffectGroup {
    u8 pad_00[8];
    EffectSlot *slots;
    u8 pad_0c[0x15 - 0xc];
    u8 count;
    u8 pad_16[0x40 - 0x16];
    TrailSlot *trails;
    u8 pad_44[4];
    GroupModel models[6];
} EffectGroup;

extern void func_0200dc4c(void *base, u32 count, u32 width, void *compare, void *work);
extern int func_ov059_020cdc6c(const void *a, const void *b);
extern int MapStateToEvenIndex(EffectParams *params);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void NegateVecFx32(VecFx32 *vec);
extern void BuildBasisFromForward(const VecFx32 *forward, const VecFx32 *up, MtxFx33 *basis);
extern void NNS_G3dMdlSetMdlPolygonID(void *model, u32 matId, int polygonId);
extern void AnimRequest_ApplyFrame(EffectParams *params, GroupModel *model);
extern void SceneNode_Draw(GroupModel *model);
extern int *func_01ffb2f8(GroupModel *model, int channel, int frame);

void EffectGroup_Draw(EffectGroup *group)
{
    EffectSlot *visible[20];
    u8 sortWork[0x20];
    MtxFx33 basis;
    VecFx32 frontForward;
    VecFx32 backForward;
    VecFx32 frontNormal;
    MtxFx33 frontRaw;
    MtxFx33 frontBasis;
    VecFx32 backNormal;
    VecFx32 direction;
    MtxFx33 backRaw;
    MtxFx33 backBasis;
    int visibleCount;
    EffectParams *params;
    int modelIndex;
    int count = group->count;
    int i;

    visibleCount = 0;
    for (i = 0; i < count; i++) {
        EffectSlot *slot = &group->slots[i];

        if (slot->owner != -1) {
            visible[visibleCount++] = slot;
        }
    }
    if (visibleCount != 0) {
        func_0200dc4c(visible, visibleCount, 4, func_ov059_020cdc6c, sortWork);
        for (i = 0; i < visibleCount; i++) {
            EffectSlot *slot = visible[i];
            GroupModel *model;

            params = slot->params;
            if (slot->owner == 2) {
                continue;
            }
            modelIndex = MapStateToEvenIndex(params);
            if (modelIndex != 0) {
                model = &group->models[modelIndex];
            } else {
                model = &slot->model;
            }
            if (modelIndex == 4) {
                VEC_Normalize(&slot->velocity, &frontNormal);
                *(VecFx32 *)&frontForward = *(VecFx32 *)&frontNormal;
                BuildBasisFromForward(&frontForward, &params->axis, &frontRaw);
                *(MtxFx33 *)&frontBasis = *(MtxFx33 *)&frontRaw;
                *(MtxFx33 *)&basis = *(MtxFx33 *)&frontBasis;
            } else {
                VEC_Normalize(&slot->velocity, &backNormal);
                *(VecFx32 *)&direction = *(VecFx32 *)&backNormal;
                NegateVecFx32(&direction);
                *(VecFx32 *)&backForward = *(VecFx32 *)&direction;
                BuildBasisFromForward(&backForward, &params->axis, &backRaw);
                *(MtxFx33 *)&backBasis = *(MtxFx33 *)&backRaw;
                *(MtxFx33 *)&basis = *(MtxFx33 *)&backBasis;
            }
            params->axis = *(VecFx32 *)&basis._10;
            model->rotation = basis;
            model->flags &= ~0x20;
            if (modelIndex != 0) {
                model->position = slot->model.position;
            }
            if (modelIndex != 2) {
                NNS_G3dMdlSetMdlPolygonID(model->resModel, 3, i % 31);
            }
            AnimRequest_ApplyFrame(params, model);
            SceneNode_Draw(model);
        }
    }
    for (i = 0; i < 10; i++) {
        if (group->trails[i].frame != -1) {
            group->models[group->trails[i].modelIndex].position = group->trails[i].position;
            func_01ffb2f8(&group->models[group->trails[i].modelIndex], 0, group->trails[i].frame);
            func_01ffb2f8(&group->models[group->trails[i].modelIndex], 2, group->trails[i].frame);
            SceneNode_Draw(&group->models[group->trails[i].modelIndex]);
        }
    }
}
