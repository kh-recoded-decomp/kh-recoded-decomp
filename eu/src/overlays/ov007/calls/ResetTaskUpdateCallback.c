#include "nitro/types.h"

typedef struct TaskCallbacks {
    void (*update)(void *task);
    void *unk_04;
    void (*draw)(void *task);
    void *data;
    u8 result;
} TaskCallbacks;

extern void EvaluateSceneEntryFlag40Trigger(void *task);

void ResetTaskUpdateCallback(TaskCallbacks *task)
{
    task->update = EvaluateSceneEntryFlag40Trigger;
    task->result = 0;
}
