#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotEntry {
    u32 inUse;
    VecFx32 position;
} SlotEntry;

typedef struct SlotTable {
    u32 count;
    SlotEntry *entries;
} SlotTable;

extern void SyncStageEntryPosition_02098fbc(int index, VecFx32 *out);
extern SlotEntry *SlotTable_GetEntry_020a125c(SlotTable *table, int index);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);

int SlotTable_FindNearestFree_020a1280(SlotTable *table, fx32 height, int heightSign, int distanceSign)
{
    fx32 bestDistance = 0;
    int best = -1;
    VecFx32 origin;
    VecFx32 delta;
    u32 i;

    SyncStageEntryPosition_02098fbc(1, &origin);
    for (i = 0; i < table->count; i++) {
        SlotEntry *entry = SlotTable_GetEntry_020a125c(table, i);
        fx32 distance;

        if (entry == NULL) {
            break;
        }
        if (entry->inUse) {
            continue;
        }
        if (heightSign > 0 && entry->position.y < height) {
            continue;
        }
        if (heightSign < 0 && entry->position.y > height) {
            continue;
        }
        VEC_Subtract_01ff9e3c(&origin, &entry->position, &delta);
        delta.y = 0;
        distance = VEC_Mag_01ff9f28(&delta);
        if (best >= 0) {
            if (distanceSign > 0 && distance < bestDistance) {
                continue;
            }
            if (distanceSign < 0 && distance > bestDistance) {
                continue;
            }
        }
        best = i;
        bestDistance = distance;
    }
    return best;
}
