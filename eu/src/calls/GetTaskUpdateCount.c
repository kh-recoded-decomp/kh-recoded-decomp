#include "src/runtime/TaskRuntime.h"

u32 GetTaskUpdateCount(void)
{
    return gTaskManager.updateCount;
}
