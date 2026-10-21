#include "nitro/types.h"
#include "src/overlays/ov041/StageCaption.h"

extern void (*gStageCaptionStates[])(StageCaption *caption);
extern BOOL HasPendingSceneValue(void);
extern void func_ov041_020cefb4(StageCaption *caption);

/* Runs the caption for a frame: redraws it when it comes back from hidden, then runs its state's handler. */
void UpdateStageCaption(StageCaption *caption)
{
    BOOL hidden = HasPendingSceneValue();
    void (*handler)(StageCaption *caption);

    if (caption->hidden && !hidden) {
        func_ov041_020cefb4(caption);
    }
    caption->hidden = hidden;
    handler = gStageCaptionStates[caption->state];
    if (handler != NULL) {
        handler(caption);
    }
}
