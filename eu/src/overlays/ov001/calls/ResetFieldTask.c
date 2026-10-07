#include "src/overlays/ov001/FieldTaskState.h"

extern void UpdateFieldTask(FieldTaskState *task);

FieldTaskState *ResetFieldTask(FieldTaskState *task)
{
    task->update = UpdateFieldTask;
    task->active = FALSE;
    return task;
}
