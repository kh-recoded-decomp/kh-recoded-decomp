#include "src/runtime/TaskRuntime.h"

extern TaskObject *DestroyRegisteredObject(TaskObject *task);

TaskObject *DestroyTaskObjectWrapper(TaskObject *task)
{
    return DestroyRegisteredObject(task);
}
