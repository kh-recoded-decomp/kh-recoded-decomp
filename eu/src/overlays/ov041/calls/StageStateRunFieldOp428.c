#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

extern void InvokeFieldModeOp428(void);
extern void SetStageState(int state, BOOL runNow);

/* Stage state 18: runs field mode op 0x428, sets work flag 0x4000 and moves on to state 20 next frame. */
void StageStateRunFieldOp428(void)
{
    StageWork *work = gMovieContextState->stageWork;

    InvokeFieldModeOp428();
    work->flags |= STAGE_WORK_FIELD_OP_DONE;
    SetStageState(0x14, FALSE);
}
