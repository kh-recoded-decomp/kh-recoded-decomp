#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

extern void BeginScreenFadeOut(int mode);
extern void SetStageState(int state, BOOL runNow);

/* Stage state 20: fades the screen out (mode 1 after the field op, 2 otherwise) and moves on to state 21. */
void StageStateFadeOut(void)
{
    StageContext *context = gMovieContextState;

    BeginScreenFadeOut((context->stageWork->flags & STAGE_WORK_FIELD_OP_DONE) ? 1 : 2);
    context->flags |= 0x20;
    SetStageState(0x15, TRUE);
}
