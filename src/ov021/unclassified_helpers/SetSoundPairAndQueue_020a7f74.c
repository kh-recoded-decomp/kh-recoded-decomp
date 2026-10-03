#include "nitro/types.h"

typedef struct SoundPair {
    u8 pad_00[0x28];
    int first;
    int second;
} SoundPair;

extern void QueueSoundCommandForArc_0204d670(int soundId);

void SetSoundPairAndQueue_020a7f74(SoundPair *pair, int first, int second)
{
    pair->first = first;
    QueueSoundCommandForArc_0204d670(first);
    if (second >= 0) {
        pair->second = second;
        QueueSoundCommandForArc_0204d670(second);
    }
}
