#include "nitro/types.h"

typedef struct {
    u32 state;
    u32 unk_04;
    u8 pad_08[0x10];
    s32 targetIndex;
    u8 pad_1c[0x08];
    u32 unk_24;
    u32 unk_28;
} Actor;

extern void ClearSessionPackedBit(int eventId);

void func_ov010_020a0cf8(Actor *actor)
{
    actor->state = 2;
    actor->unk_04 = 0;
    actor->unk_28 = 0;
    actor->targetIndex = -1;
    actor->unk_24 = 0;
    ClearSessionPackedBit(0x3716);
    ClearSessionPackedBit(0x3717);
}
