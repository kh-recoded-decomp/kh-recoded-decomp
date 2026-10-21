#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

/* TRUE while a HUD message is shown with more than one frame left. */
BOOL IsStageHudMessageShowing(void)
{
    StageHudMessage *message = &gMovieContextState->stageWork->hudMessage;

    return message->timer > 1 && (message->flags & STAGE_HUD_MESSAGE_SHOWN);
}
