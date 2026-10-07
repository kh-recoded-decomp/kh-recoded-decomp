#include "src/overlays/ov001/FieldTaskState.h"

extern void CheckSceneEntryTrigger(FieldTaskState *task);

FieldTaskState *ResetSceneEntryTrigger(FieldTaskState *task)
{
    task->update = CheckSceneEntryTrigger;
    task->active = FALSE;
    return task;
}
