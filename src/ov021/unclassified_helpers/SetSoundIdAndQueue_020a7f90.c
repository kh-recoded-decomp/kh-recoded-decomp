#include "nitro/types.h"

typedef struct SoundOwner {
    u8 pad_00[0x34];
    int soundId;
} SoundOwner;

extern void QueueSoundCommandForArc_0204d670(int soundId);

void SetSoundIdAndQueue_020a7f90(SoundOwner *owner, int soundId)
{
    owner->soundId = soundId;
    if (soundId >= 0) {
        QueueSoundCommandForArc_0204d670(soundId);
    }
}
