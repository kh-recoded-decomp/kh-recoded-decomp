#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);

/* Plays a sound when an entry's animation reaches a frame (within that frame's span). */
void PlaySoundOnEntryFrame(StageEntry *entry, int animation, fx32 frame, int seqArcNo, int index, fx32 soundFrame)
{
    if (MatchesEitherSlotId(entry, (u8)animation) && soundFrame <= frame && frame < soundFrame + FX32_ONE) {
        PlayStageSound(seqArcNo, index, TRUE);
    }
}
