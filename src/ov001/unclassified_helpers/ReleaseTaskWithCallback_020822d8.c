#include "nitro/types.h"

typedef struct CallbackTask CallbackTask;

typedef struct CallbackTask {
    u8 pad_00[0x8];
    void *work;
    u8 pad_0C[0x5C];
    void (*onFinish)(CallbackTask *task);
} CallbackTask;

extern void ReleaseWorkResources_020822ac(void *work);
extern void ReleaseTaskBase_0207f20c(CallbackTask *task, int arg);

void ReleaseTaskWithCallback_020822d8(CallbackTask *task, int arg)
{
    if (task->onFinish != NULL) {
        task->onFinish(task);
    }
    ReleaseWorkResources_020822ac(task->work);
    ReleaseTaskBase_0207f20c(task, arg);
}
