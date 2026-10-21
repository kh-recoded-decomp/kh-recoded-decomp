#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void (*gStageCaptionStates[])(StageCaption *caption);
extern void SetStageCaptionState(StageCaption *caption, int state);
extern void ResetStageCaptionLines(StageCaption *caption);

/* Puts the caption back in state 0 with no lines and runs that state once. */
void RestartStageCaption(StageCaption *caption)
{
    SetStageCaptionState(caption, 0);
    ResetStageCaptionLines(caption);
    gStageCaptionStates[caption->state](caption);
}
