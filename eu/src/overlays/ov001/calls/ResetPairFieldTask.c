#include "src/overlays/ov001/FieldTaskState.h"

extern void EventTrigger_EvaluateCallback(FieldTaskState *task);

FieldTaskState *ResetPairFieldTask(FieldTaskState *task)
{
    task->update = EventTrigger_EvaluateCallback;
    task->active = FALSE;
    return task;
}
