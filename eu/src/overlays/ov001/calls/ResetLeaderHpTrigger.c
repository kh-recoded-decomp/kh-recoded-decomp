#include "src/overlays/ov001/FieldTaskState.h"

extern void CheckLeaderHpTrigger(FieldTaskState *task);

FieldTaskState *ResetLeaderHpTrigger(FieldTaskState *task)
{
    task->update = CheckLeaderHpTrigger;
    task->active = FALSE;
    return task;
}
