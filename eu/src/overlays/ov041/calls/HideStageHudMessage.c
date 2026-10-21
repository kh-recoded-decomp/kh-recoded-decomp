#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

extern BOOL IsStageHudMessageShowing(void);
extern void HideHudCaption(void);

/* Takes down the HUD message if one is showing. */
void HideStageHudMessage(void)
{
    StageHudMessage *message = &gMovieContextState->stageWork->hudMessage;

    if (IsStageHudMessageShowing()) {
        message->kind = 0;
        message->flags &= (u8)~STAGE_HUD_MESSAGE_SHOWN;
        message->timer = 0;
        HideHudCaption();
    }
}
