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

#pragma opt_propagation off
void CARDi_InitResourceLock_020092b8(void)
{
    CardCommon *common = &data_02056fe0;

    common->lockOwner = -3;
    common->lockRef = 0;
    common->lockTarget = 0;
    common->lockQueue.head = common->lockQueue.tail = NULL;
}
#pragma opt_propagation reset
