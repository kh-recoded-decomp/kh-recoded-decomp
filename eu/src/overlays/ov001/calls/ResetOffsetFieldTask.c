#include "src/overlays/ov001/FieldTaskState.h"

extern void EventTrigger_CheckCounterGoal(FieldTaskState *task);

FieldTaskState *ResetOffsetFieldTask(FieldTaskState *task)
{
    task->update = EventTrigger_CheckCounterGoal;
    task->active = FALSE;
    return task;
}
