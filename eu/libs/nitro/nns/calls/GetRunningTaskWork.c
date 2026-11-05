#include "src/runtime/TaskRuntime.h"

/* Requires a running task. This is not a heap lookup. */
void *GetRunningTaskWork(void)
{
    return gTaskManager.current->work;
}
