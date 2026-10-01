#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEntryInfo {
    u16 unk_00;
    u16 activeFlag;
} StageEntryInfo;

typedef struct StageEntryObject {
    u8 pad_000[0x1d4];
    StageEntryInfo *info;
} StageEntryObject;

extern StageEntryObject *CacheStageEntryValue_02099248(u16 id);
extern void SyncStageEntryPosition_02098fbc(u16 id, VecFx32 *outPosition);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);

u16 FindNearestStageEntry_02099328(const VecFx32 *target)
{
    u16 nearestId = 0;
    fx32 nearestDistance;
    int i;
    VecFx32 delta;
    VecFx32 position;

    for (i = 0; i < 3; i++) {
        int id = i + 1;
        StageEntryObject *entry = CacheStageEntryValue_02099248(id);
        fx32 distance;

        if (entry == NULL) {
            break;
        }
        if (entry->info->activeFlag == 0) {
            continue;
        }
        SyncStageEntryPosition_02098fbc(id, &position);
        VEC_Subtract_01ff9e3c(&position, target, &delta);
        delta.y = 0;
        distance = VEC_Mag_01ff9f28(&delta);
        if (nearestId == 0 || distance < nearestDistance) {
            nearestDistance = distance;
            nearestId = id;
        }
    }
    return nearestId;
}
