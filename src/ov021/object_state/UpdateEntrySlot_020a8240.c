#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s8 inUse;
    s8 actorId;
    s8 anchorMode;
    u8 pad_03;
    u16 flags;
    u8 pad_06[2];
    u8 tracks[0xa4];
    u8 payload[0x60];
    fx32 fixedDelta;
    s16 endMask;
    u8 pad_112[2];
    u32 soundHandle;
    u8 pad_118[4];
    VecFx32 worldPos;
    u8 screenPos[0x10];
} EntrySlot;

extern int ProjectWorldToScreenFx_0206ad34(VecFx32 *world, void *screen);
extern BOOL func_0204dc3c(u32 handle);
extern void Handle_WritePayloadIfLive_0204db9c(u32 handle, void *payload);
extern u16 AdvanceAnimationTracks_0202ef24(void *tracks, fx32 delta);

void UpdateEntrySlot_020a8240(EntrySlot *slot, int actorId, fx32 delta)
{
    s16 ended;

    if (slot->inUse != 0 && slot->actorId == actorId && slot->inUse == 1) {
        if (slot->anchorMode == 3 && !(slot->flags & 0x20)) {
            slot->flags |= 2;
            if (ProjectWorldToScreenFx_0206ad34(&slot->worldPos, slot->screenPos) >= 0) {
                slot->flags &= ~2;
            }
        }
        if (slot->soundHandle != 0 && !(slot->flags & 0x40)) {
            if (!func_0204dc3c(slot->soundHandle)) {
                slot->soundHandle = 0;
            } else {
                Handle_WritePayloadIfLive_0204db9c(slot->soundHandle, slot->payload);
            }
        }
        if (slot->flags & 0x100) {
            delta = slot->fixedDelta;
        }
        ended = AdvanceAnimationTracks_0202ef24(slot->tracks, delta);
        if ((slot->endMask & ended) && !(slot->flags & 4)) {
            slot->inUse = 0;
        }
    }
}
