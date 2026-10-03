#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xa4];
    VecFx32 position;
    u8 pad_0b0[0x130 - 0xb0];
    s32 phase;
} EffectSlot;

extern VecFx32 data_ov058_020d8a2c;

extern u16 AdvanceAnimationTracks_0202ef24(EffectSlot *slot, int delta);
extern void RebindEmitterSlots_020d7498(EffectSlot *slot, int track);

void UpdateEffectSlotPhase_020d7640(EffectSlot *slot, int delta)
{
    VecFx32 position;

    if (slot->phase == 0) {
        return;
    }
    position = data_ov058_020d8a2c;
    if (slot->phase == 4) {
        position.y += 0x2000;
    }
    slot->position = position;
    switch (slot->phase) {
    case 1:
        if (AdvanceAnimationTracks_0202ef24(slot, delta) != 0) {
            RebindEmitterSlots_020d7498(slot, 1);
            slot->phase = 2;
        }
        break;
    case 2:
        AdvanceAnimationTracks_0202ef24(slot, delta);
        break;
    case 3:
        if (AdvanceAnimationTracks_0202ef24(slot, delta) != 0) {
            slot->phase = 0;
        }
        break;
    }
}
