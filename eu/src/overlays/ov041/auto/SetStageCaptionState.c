#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

/* Moves the caption to another state, remembering the one it leaves. */
void SetStageCaptionState(StageCaption *caption, int state)
{
    caption->previousState = caption->state;
    caption->state = state;
}
