#include "src/overlays/ov001/FieldTaskState.h"

extern void EventTrigger_Evaluate(FieldTaskState *task);

FieldTaskState *ResetEventTrigger(FieldTaskState *task)
{
    task->update = EventTrigger_Evaluate;
    task->active = FALSE;
    return task;
}
