#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x22c];
} ModelSet;

typedef struct {
    u8 pad_000[0x928];
    u64 flags;
    u8 pad_930[0x9d4 - 0x930];
    ModelSet modelSets[2];
} Actor;

extern void SetBit1WhenBit0Set_020a9ce8(u32 *flags, s32 enable);

void Actor_SetModelSetsVisible_020cd078(Actor *actor, BOOL enable)
{
    int i;

    for (i = 0; i < 2; i++) {
        SetBit1WhenBit0Set_020a9ce8(&actor->modelSets[i].flags, enable);
    }
    if (!enable) {
        actor->flags &= ~0x40ULL;
    } else {
        actor->flags |= 0x40;
    }
}
