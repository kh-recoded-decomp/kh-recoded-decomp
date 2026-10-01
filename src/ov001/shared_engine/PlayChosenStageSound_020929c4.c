#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u32 PlayStageSoundAt_0209d080(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);

void PlayChosenStageSound_020929c4(VecFx32 *position, s32 seqArcA, s32 soundA, s32 seqArcB, u16 soundB, BOOL useFirst)
{
    if (useFirst) {
        if (soundA != 0) {
            PlayStageSoundAt_0209d080(seqArcA, soundA, position, 0);
        }
    } else if (soundB != 0) {
        PlayStageSoundAt_0209d080(seqArcB, soundB, position, 0);
    }
}
