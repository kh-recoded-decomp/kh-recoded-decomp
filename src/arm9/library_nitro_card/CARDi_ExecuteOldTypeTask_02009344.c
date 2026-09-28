#include "nitro/types.h"

typedef struct CardCommand {
    s32 result;
} CardCommand;

typedef struct CardCommon CardCommon;
typedef void (*CardTaskFunc)(CardCommon *common);

struct CardCommon {
    CardCommand *command;
    volatile u32 flags;
    u32 priority;
    u8 pad_0c[0x28 - 0x0c];
    u8 thread[0x4e8 - 0x28];
    CardTaskFunc taskFunc;
};

extern CardCommon data_02056fe0;
extern BOOL OS_SetThreadPriority_02002bd0(void *thread, u32 priority);
extern void OS_WakeupThreadDirect_02002b60(void *thread);
extern void CARDi_EndTask_02009434(CardCommon *common);

BOOL CARDi_ExecuteOldTypeTask_02009344(CardTaskFunc task, BOOL async)
{
    CardCommon *common = &data_02056fe0;

    if (async) {
        OS_SetThreadPriority_02002bd0(common->thread, common->priority);
        common->taskFunc = task;
        common->flags |= 8;
        OS_WakeupThreadDirect_02002b60(common->thread);
    } else {
        task(common);
        CARDi_EndTask_02009434(common);
    }
    return async ? TRUE : (common->command->result == 0);
}
