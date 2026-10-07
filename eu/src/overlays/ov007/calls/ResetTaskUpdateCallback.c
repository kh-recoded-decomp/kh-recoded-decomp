#include "nitro/types.h"

typedef struct TaskCallbacks {
    void (*update)(void *task);
    void *unk_04;
    void (*draw)(void *task);
    void *data;
    u8 result;
} TaskCallbacks;

extern void func_ov007_020a1ba0(void *task);

void ResetTaskUpdateCallback(TaskCallbacks *task)
{
    task->update = func_ov007_020a1ba0;
    task->result = 0;
}
