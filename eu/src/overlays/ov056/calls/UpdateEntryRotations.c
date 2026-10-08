#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ModelEntry {
    u8 pad_000[2];
    s8 modelId;
    u8 pad_003[0x24 - 0x3];
    VecFx32 direction;
    u16 nodeFlags;
    u8 pad_032[0xb0 - 0x32];
    MtxFx33 rotation;
    u8 pad_0d4[0x154 - 0xd4];
} ModelEntry;

typedef struct ModelGroup {
    u8 pad_00[8];
    ModelEntry *entries;
    u8 pad_0c[0x15 - 0xc];
    u8 entryCount;
    u8 pad_16[0x40 - 0x16];
    s8 groupFlags;
    u8 pad_41[3];
    u16 groupNode;
} ModelGroup;

extern VecFx32 data_ov056_020d7fb4;
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void func_ov021_020ae8ac(u16 *node);

void UpdateEntryRotations(ModelGroup *group)
{
    ModelEntry *entry;
    int entryIndex;

    for (entryIndex = 0; entryIndex < group->entryCount; entryIndex++) {
        entry = &group->entries[entryIndex];
        if (entry->modelId != -1) {
            MtxFx33 rotation;
            VecFx32 xAxis;
            VecFx32 yAxis;
            VecFx32 zAxis;

            VEC_Normalize(&entry->direction, &zAxis);
            VEC_CrossProduct(&data_ov056_020d7fb4, &zAxis, &xAxis);
            VEC_Normalize(&xAxis, &xAxis);
            VEC_CrossProduct(&zAxis, &xAxis, &yAxis);
            rotation._00 = xAxis.x;
            rotation._01 = xAxis.y;
            rotation._02 = xAxis.z;
            rotation._10 = yAxis.x;
            rotation._11 = yAxis.y;
            rotation._12 = yAxis.z;
            rotation._20 = zAxis.x;
            rotation._21 = zAxis.y;
            rotation._22 = zAxis.z;
            entry->rotation = rotation;
            entry->nodeFlags &= ~0x20;
            func_ov021_020ae8ac(&entry->nodeFlags);
        }
    }
    if (group->groupFlags & 1) {
        func_ov021_020ae8ac(&group->groupNode);
    }
}
