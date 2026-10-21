#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

typedef float f32;

/* A whole frame count as fx32, rounded half away from zero (the float converts on assignment). */
#define FRAME_TO_FX32_ROUNDED(x) ((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f)

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern void PlaySoundOnEntryFrame(StageEntry *entry, int animation, fx32 frame, int seqArcNo, int index,
                                  fx32 soundFrame);

/* Plays the sound of an entry's action when its animation reaches the action's sound frame. */
void PlayEntryActionSound(StageEntry *entry, fx32 frame)
{
    StageEntryAction *action = GetEntryAction(entry);
    fx32 soundFrame = FRAME_TO_FX32_ROUNDED(action->soundFrame);
    s32 index = action->soundIndex;
    s32 seqArcNo = action->soundSeqArc;

    if (seqArcNo >= 0 && seqArcNo <= 0x1a0 && index >= 0) {
        PlaySoundOnEntryFrame(entry, action->animation, frame, seqArcNo, index, soundFrame);
    }
}
