#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern BOOL func_ov041_020ce81c(StageCaption *caption, StageTextLine *lines, int count);
extern void ResetStageCaptionLines(StageCaption *caption);
extern void SetStageCaptionState(StageCaption *caption, int state);

/* Caption state 2: shows the queued lines; once all are out, clears them and goes idle (state 5). */
void StageCaptionState2(StageCaption *caption)
{
    if (!func_ov041_020ce81c(caption, caption->queued, caption->queuedCount)) {
        return;
    }
    if (caption->lineCount < caption->queuedCount) {
        return;
    }
    ResetStageCaptionLines(caption);
    SetStageCaptionState(caption, 5);
}
