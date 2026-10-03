#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MapPoint {
    fx32 x;
    fx32 y;
} MapPoint;

typedef struct DrawEntry {
    u8 link[0xc];
    MapPoint pos;
    s32 priority;
    u8 pad_18[0x4];
    u8 subPriority;
    u8 pad_1D[0x3];
} DrawEntry;

typedef struct DrawList {
    u8 pad_0000[0x686c];
    s32 scratchCount;
    s32 maxLevel;
    u8 list[0xc];
    DrawEntry pool[64];
    s32 poolCapacity;
    s32 poolUsed;
    DrawEntry scratch[1];
} DrawList;

extern s32 SqrtResultRounded_020b6184(void);
extern DrawEntry *NNS_FndGetNextListObject_02012a38(void *list, DrawEntry *obj);
extern void RemoveIntrusiveListObject_020129d8(void *list, DrawEntry *obj);
extern void func_01ff89a8(const void *src, void *dest, u32 size);
extern void InsertSortedDrawEntry_020b6408(DrawList *owner, DrawEntry *entry, s32 priority, int subPriority);

DrawEntry *AllocDrawEntry_020b6460(DrawList *owner, int unused, const MapPoint *pos, u8 subPriority)
{
    s32 distance;
    DrawEntry *entry;

    if (owner->poolCapacity == 0) {
        entry = &owner->scratch[owner->scratchCount];
        owner->scratchCount++;
    } else {
        if (owner->poolUsed < owner->poolCapacity) {
            entry = &owner->pool[owner->poolUsed];
            owner->poolUsed++;
            distance = SqrtResultRounded_020b6184();
        } else {
            entry = NNS_FndGetNextListObject_02012a38(owner->list, NULL);
            distance = SqrtResultRounded_020b6184();
            if (distance < entry->priority) {
                entry = &owner->scratch[owner->scratchCount];
        owner->scratchCount++;
                goto fill;
            }
            RemoveIntrusiveListObject_020129d8(owner->list, entry);
            func_01ff89a8(entry, &owner->scratch[owner->scratchCount], sizeof(DrawEntry));
            owner->scratchCount++;
        }
        InsertSortedDrawEntry_020b6408(owner, entry, distance, subPriority);
    }
fill:
    entry->priority = distance;
    entry->subPriority = subPriority;
    func_01ff89a8(pos, &entry->pos, sizeof(MapPoint));
    return entry;
}
