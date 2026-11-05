#include "src/runtime/TaskRuntime.h"

TaskObject *GetCurrentTaskObject(void)
{
    return gTaskManager.current;
}
