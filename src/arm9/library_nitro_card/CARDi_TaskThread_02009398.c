#include "nitro/types.h"

typedef struct CardCommon CardCommon;
typedef void (*CardTaskFunc)(CardCommon *common);

struct CardCommon {
    void *command;
    volatile u32 flags;
    u8 pad_08[0x4e8 - 0x08];
    CardTaskFunc taskFunc;
};

extern CardCommon data_02056fe0;
extern int OS_DisableInterrupts_02004938(void);
extern int OS_RestoreInterrupts_0200494c(int state);
extern void OS_SleepThread_02002aa8(void *queue);
extern BOOL CARDi_ExecuteOldTypeTask_02009344(CardTaskFunc task, BOOL async);

void CARDi_TaskThread_02009398(void *arg)
{
    CardCommon *const common = &data_02056fe0;

    for (;;) {
        int savedState = OS_DisableInterrupts_02004938();
        for (;;) {
            if (common->flags & 8) {
                break;
            }
            OS_SleepThread_02002aa8(NULL);
        }
        OS_RestoreInterrupts_0200494c(savedState);
        CARDi_ExecuteOldTypeTask_02009344(common->taskFunc, FALSE);
    }
}
