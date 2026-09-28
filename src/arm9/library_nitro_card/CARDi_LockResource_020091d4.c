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
extern void OS_SleepThread_02002aa8(CardThreadQueue *queue);

#pragma opt_rotateloops off
void CARDi_LockResource_020091d4(s32 owner, u32 target)
{
    CardCommon *const common = &data_02056fe0;
    int savedState = OS_DisableInterrupts_02004938();

    if (common->lockOwner == owner) {
        if (common->lockTarget != target) {
            OS_Terminate_02004cf0();
        }
    } else {
        while (common->lockOwner != -3) {
            OS_SleepThread_02002aa8(&common->lockQueue);
        }
        common->lockOwner = owner;
        common->lockTarget = target;
    }
    ++common->lockRef;
    OS_RestoreInterrupts_0200494c(savedState);
}
#pragma opt_rotateloops reset
