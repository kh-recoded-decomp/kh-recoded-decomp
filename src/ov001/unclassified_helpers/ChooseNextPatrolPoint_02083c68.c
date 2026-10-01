#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotEntry {
    VecFx32 *points;
    u8 count;
} SlotEntry;

typedef struct PatrolObject {
    u8 pad_00[0x7f];
    s8 lastPoint;
    s8 targetPoint;
    s8 visits;
} PatrolObject;

extern SlotEntry *FindActiveSlotEntry_02083c38(PatrolObject *object);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern signed char GetCtxModeByte_02068084(void);
extern int func_ov001_02067ed4(void);
extern u32 func_ov001_02068254(int kind);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

void ChooseNextPatrolPoint_02083c68(PatrolObject *object)
{
    SlotEntry *entry;
    VecFx32 *target;
    u8 bestPoint;
    fx32 bestDistance;
    u8 i;
    u8 count;
    s8 point;
    fx32 distance;

    entry = FindActiveSlotEntry_02083c38(object);
    target = func_ov001_0206dc4c(0);
    if (object->visits < 3 || GetCtxModeByte_02068084() == 7) {
        if (GetCtxModeByte_02068084() == 7) {
            object->targetPoint = (object->targetPoint + 1) % (s8)entry->count;
            return;
        }
        bestDistance = 0x80000000;
        count = entry->count;
        for (i = 1; i < count; i++) {
            point = (i + object->lastPoint) % count;
            distance = func_01ffa0f4(&entry->points[point], target);
            if (distance > 0x6000) {
                object->targetPoint = point;
                return;
            }
            if (bestDistance < distance) {
                bestDistance = distance;
                bestPoint = point;
            }
        }
        object->targetPoint = bestPoint;
        return;
    }
    object->targetPoint = -((s8)random_next_scaled_0202aa04(func_ov001_02068254(func_ov001_02067ed4())) + 1);
}
