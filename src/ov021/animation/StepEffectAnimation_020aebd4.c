#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimatedEffect {
    u8 pad00[0x40];
    s8 flags;
    u8 pad41[3];
    u8 tracks[1];
} AnimatedEffect;

extern BOOL AdvanceAnimationTracks_0202ef24(void *tracks, fx32 step);

BOOL StepEffectAnimation_020aebd4(AnimatedEffect *effect, fx32 step)
{
    if ((effect->flags & 1) && AdvanceAnimationTracks_0202ef24(effect->tracks, step)) {
        effect->flags &= ~1;
    }
    if (effect->flags & 1) {
        return FALSE;
    }
    return TRUE;
}
