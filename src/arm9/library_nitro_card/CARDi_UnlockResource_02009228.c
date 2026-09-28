#include "nitro/types.h"

typedef struct CardThreadQueue {
    void *head;
    void *tail;
} CardThreadQueue;

typedef struct CardCommon {
    u8 pad_00[0x14];
    s32 lockOwner;
    s32 lockRef;
    CardThreadQueue lockQueue;
    u32 lockTarget;
} CardCommon;

extern CardCommon data_02056fe0;
extern int OS_DisableInterrupts_02004938(void);
extern int OS_RestoreInterrupts_0200494c(int state);
extern void OS_Terminate_02004cf0(void);
extern void OS_WakeupThread_02002af8(CardThreadQueue *queue);

void CARDi_UnlockResource_02009228(s32 owner, u32 target)
{
    CardCommon *common = &data_02056fe0;
    int savedState = OS_DisableInterrupts_02004938();

    if (common->lockOwner != owner || !common->lockRef) {
        OS_Terminate_02004cf0();
    } else {
        if (common->lockTarget != target) {
            OS_Terminate_02004cf0();
        }
        if (!--common->lockRef) {
            common->lockOwner = -3;
            common->lockTarget = 0;
            OS_WakeupThread_02002af8(&common->lockQueue);
        }
    }
    OS_RestoreInterrupts_0200494c(savedState);
}
