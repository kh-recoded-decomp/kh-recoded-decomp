#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPoint {
    VecFx32 position;
    u32 unk_0C;
    u16 nextSlot;
    u16 pad_12;
} SlotPoint;

typedef struct TargetCandidate {
    s32 kind;
    void *object;
    u8 pad_08[0xc];
} TargetCandidate;

typedef struct Manager {
    u32 flags;
    TargetCandidate current;
    u8 pad_18[0x30];
    s32 lockRange;
} Manager;

extern Manager *g_manager_020a0484;
extern s32 func_ov001_02087928(void);
extern s32 func_ov001_02087944(s32 startIndex);
extern BOOL StageRecord_GetSlotPosition_02087c4c(u32 id, u32 slot, void *outPoint);
extern BOOL func_ov001_0206b800(void *origin, s32 recordId, u16 slot, s32 range);
extern BOOL CheckSideOffsetInRange_0206b3d4(const VecFx32 *position, const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern TargetCandidate *func_ov001_0206b948(TargetCandidate *candidate, s16 recordId, s16 slot);

BOOL ScanRecordSlotsForSideTarget_0206b334(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset)
{
    Manager *manager = g_manager_020a0484;
    BOOL found = FALSE;
    s32 recordId;
    u16 slot;
    SlotPoint point;

    if (!(manager->flags & 0x80)) {
        return found;
    }
    for (recordId = func_ov001_02087928(); recordId != 0; recordId = func_ov001_02087944(recordId)) {
        s16 shortId;

        point.nextSlot = 0;
        shortId = recordId;
        do {
            slot = point.nextSlot;
            if (StageRecord_GetSlotPosition_02087c4c(recordId, slot, &point) &&
                func_ov001_0206b800(NULL, recordId, slot, manager->lockRange) &&
                CheckSideOffsetInRange_0206b3d4(&point.position, facing, low, high, direction, outOffset)) {
                func_ov001_0206b948(&manager->current, shortId, slot);
                high = *outOffset;
                found = TRUE;
            }
        } while (point.nextSlot != 0);
    }
    return found;
}
