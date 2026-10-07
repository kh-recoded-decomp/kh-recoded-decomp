#include "src/overlays/ov001/FieldTaskState.h"

extern int func_ov001_02067ed4(void);
extern int IsSceneEntryFlag2Set(int value);
extern int func_ov001_02069464(FieldTaskState *task);

int CheckSceneEntryTrigger(FieldTaskState *task)
{
    int result;

    task->active = FALSE;
    result = func_ov001_02067ed4();
    if ((s8)task->kind != result) {
        return FALSE;
    }
    if (((s8)task->mode == 0) &&
        (result = IsSceneEntryFlag2Set((s16)task->id), result != 0)) {
        task->active = TRUE;
    }
    result = func_ov001_02069464(task);
    if (result != 0) {
        return (s8)task->active;
    }
    return FALSE;
}
