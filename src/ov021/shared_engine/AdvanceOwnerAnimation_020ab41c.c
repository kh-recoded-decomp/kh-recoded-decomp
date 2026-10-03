#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 flags;
    s16 frames[5];
    void *anims[5];
} AnimTrackSet;

typedef struct {
    u8 pad_00[0x30];
    AnimTrackSet tracks;
} AnimOwner;

extern fx32 func_0202f4b8(AnimTrackSet *tracks, u16 index);
extern u16 AdvanceAnimationTracks_0202ef24(AnimTrackSet *tracks, fx32 delta);

s16 AdvanceOwnerAnimation_020ab41c(AnimOwner *owner, fx32 step)
{
    int result = 1;
    AnimTrackSet *tracks = &owner->tracks;
    fx32 length = 0;
    int i;

    for (i = 0; i < 5; i++) {
        if (tracks->anims[i] != NULL && tracks->frames[i] >= 0) {
            length = func_0202f4b8(tracks, i);
            break;
        }
    }
    if (length >= step) {
        result = AdvanceAnimationTracks_0202ef24(tracks, step);
    }
    return (s16)result;
}

