#include "nitro/types.h"

typedef struct ActorSoundTrack {
    s32 timer;
    u8 pad_04[0x54];
} ActorSoundTrack;

typedef struct Actor {
    u8 pad_000[0x8e4];
    ActorSoundTrack tracks[4];
} Actor;

extern u32 func_02028940(void);
extern void func_ov001_02089948(Actor *actor, int trackIndex);

void Actor_FireExpiredTrackCues_02089180(Actor *actor)
{
    int trackIndex;

    if (func_02028940() != 0) {
        return;
    }
    for (trackIndex = 1; trackIndex < 4; trackIndex++) {
        if (actor->tracks[trackIndex].timer >= 0xcd) {
            func_ov001_02089948(actor, trackIndex);
        }
    }
}
