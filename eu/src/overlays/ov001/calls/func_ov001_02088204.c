#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StagePartySlot {
    u16 kind;
    u16 recordId;
    u8 pad_04[0x8];
    VecFx32 position;
    VecFx32 targetPosition;
    fx32 heightOffset;
    u16 timer;
} StagePartySlot;

typedef struct StageRecord {
    u8 pad_00[0x70];
    s32 hitPoints;
    s32 maxHitPoints;
} StageRecord;

extern StagePartySlot *GetStagePartySlot(u32 slot);
extern StageRecord *GetStageEventRecord(u32 id);
extern void AssignPartySlotToStageEvent(u32 slotIndex, u8 kind, u8 subKind);

void func_ov001_02088204(u32 slotIndex, u8 kind, u8 subKind, s32 hitPoints, s32 maxHitPoints, const VecFx32 *position)
{
    StagePartySlot *slot;
    StageRecord *record;

    slot = GetStagePartySlot(slotIndex);
    if (slot == NULL) {
        return;
    }
    if (slot->recordId == 0) {
        AssignPartySlotToStageEvent(slotIndex, kind, subKind);
    }
    if (slot->recordId == 0) {
        return;
    }
    record = GetStageEventRecord(slot->recordId);
    if (record != NULL) {
        record->hitPoints = hitPoints;
        record->maxHitPoints = maxHitPoints;
    }
    if (position != NULL) {
        slot->position = *position;
        slot->targetPosition = *position;
        slot->heightOffset = 0xc00;
        slot->targetPosition.y += 0xc00;
        slot->timer = 0;
    }
}
