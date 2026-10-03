#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x998];
    u8 soundPair[8];
} Actor;

extern void SetSoundPairAndQueue_020a7f74(void *pair, int first, int second);
extern void QueueSoundCommandForArc_0204d670(int soundId);

void Actor_QueueBattleSounds_020c799c(Actor *actor)
{
    SetSoundPairAndQueue_020a7f74(actor->soundPair, 0x30, 0x48);
    QueueSoundCommandForArc_0204d670(0xca);
    QueueSoundCommandForArc_0204d670(0xcb);
    QueueSoundCommandForArc_0204d670(0xcc);
    QueueSoundCommandForArc_0204d670(0xcd);
}
