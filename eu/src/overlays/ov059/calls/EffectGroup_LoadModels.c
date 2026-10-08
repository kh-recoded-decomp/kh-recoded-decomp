#include "nitro/types.h"
#include "nitro/fx_types.h"

#pragma opt_propagation off

typedef struct AnimationBlendTable AnimationBlendTable;

typedef struct SharedRecord {
    u8 pad_00[0x10];
    void *data;
} SharedRecord;

typedef struct GroupModel {
    u8 pad_00[0xb0];
    VecFx32 scale;
    u8 pad_bc[0xd8 - 0xbc];
    u8 blendTable[0x2c];
} GroupModel;

typedef struct GroupOwner {
    u8 pad_0000[0x1824];
    s32 heapGroup;
} GroupOwner;

typedef struct EffectGroup {
    u8 pad_00[0x44];
    GroupOwner *owner;
    GroupModel models[6];
} EffectGroup;

extern SharedRecord *SND_RegisterSeq(u32 fileId, int kind);
extern void *func_0202c4a0(u32 fileId, int kind);
extern void func_0202edb0(GroupModel *model, SharedRecord *resource, void *source, int extra);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void selectJointAnimationBlend(GroupModel *model, u16 trackIndex, void *blendTable, s16 blendIndex);

static inline void LoadModelSet(EffectGroup *group, u32 *ids, int count)
{
    int i = 0;

    while (i < count) {
        SharedRecord *record = SND_RegisterSeq(
            (0x80000000 | (((group->owner->heapGroup + 0x8000) & 0xfffffc) << 7)) | (ids[i] & 0x1ff), 8);
        if (record->data != NULL) {
            func_0202edb0(&group->models[i], record, NULL, 8);
        } else {
            void *block = func_0202c4a0(
                (0x80000000 | (((group->owner->heapGroup + 0x8000) & 0xfffffc) << 7)) | ((ids[i] + 1) & 0x1ff), 0x11);
            func_0202edb0(&group->models[i], record, block, 8);
            NNSi_FndFreeFromDefaultHeap(block);
        }
        group->models[i].scale.x = group->models[i].scale.y = group->models[i].scale.z = 0x1000;
        i++;
    }
}

void EffectGroup_LoadModels(EffectGroup *group, u32 *ids)
{
    LoadModelSet(group, ids, 6);
    selectJointAnimationBlend(&group->models[1], 0, group->models[1].blendTable, 0);
    selectJointAnimationBlend(&group->models[1], 2, group->models[1].blendTable, 0);
    selectJointAnimationBlend(&group->models[3], 0, group->models[3].blendTable, 0);
    selectJointAnimationBlend(&group->models[2], 0, group->models[2].blendTable, 0);
    selectJointAnimationBlend(&group->models[2], 2, group->models[2].blendTable, 0);
    selectJointAnimationBlend(&group->models[3], 2, group->models[3].blendTable, 0);
    selectJointAnimationBlend(&group->models[4], 0, group->models[4].blendTable, 0);
    selectJointAnimationBlend(&group->models[5], 0, group->models[5].blendTable, 0);
    selectJointAnimationBlend(&group->models[5], 2, group->models[5].blendTable, 0);
}
