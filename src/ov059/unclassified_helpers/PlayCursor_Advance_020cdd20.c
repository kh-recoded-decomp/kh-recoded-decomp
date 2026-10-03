#include "nitro/types.h"

typedef struct {
    u8 data[0x104];
} ResourceSlot;

typedef struct {
    u8 pad_00[0x48];
    ResourceSlot slots[6];
} EffectSet;

typedef struct {
    s32 frame;
    s32 slot;
} PlayCursor;

extern int func_0202f4b8(ResourceSlot *slot, int channel);

void PlayCursor_Advance_020cdd20(EffectSet *set, PlayCursor *cursor, int step)
{
    int length;
    int other;

    cursor->frame += step;
    length = func_0202f4b8(&set->slots[cursor->slot], 2);
    other = func_0202f4b8(&set->slots[cursor->slot], 0);
    if (other < length) {
        other = length;
    }
    if (cursor->frame >= other) {
        cursor->frame = -1;
    }
}
