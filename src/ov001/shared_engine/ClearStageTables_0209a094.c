#include "nitro/types.h"

typedef struct {
    u8 data[0x28];
} StageLink;

typedef struct {
    u8 data[0x1c8];
} StageEvent;

typedef struct {
    u8 pad_00000[0x208];
    StageLink *links;
    u32 *linkFlags;
    StageEvent *events;
    u8 pad_00214[0x17a14 - 0x214];
    u8 bufferA[0x800];
    u8 bufferB[0x600];
    u8 bufferC[0x280];
    u8 pad_18a94[0x18d7c - 0x18a94];
    void *eventPool;
    u8 pad_18d80[0x18];
    void *controllerPool;
    void *objectPool;
    u8 pad_18da0[0x44];
    u16 eventCount;
    u16 linkCount;
    u16 activeLinks;
    u8 pad_18dea[4];
    u16 pendingA;
    u8 pad_18df0[2];
    u16 pendingB;
    u8 pad_18df4[0x68];
    u32 pendingFlags;
} StageManager;

extern StageManager *data_ov001_020a0508;
extern void HandlePool_ReleaseAll_0208f21c(void *pool);
extern void func_01ff8830(void *dst, int value, u32 size);

void ClearStageTables_0209a094(void)
{
    HandlePool_ReleaseAll_0208f21c(data_ov001_020a0508->eventPool);
    HandlePool_ReleaseAll_0208f21c(data_ov001_020a0508->controllerPool);
    HandlePool_ReleaseAll_0208f21c(data_ov001_020a0508->objectPool);
    func_01ff8830(data_ov001_020a0508->events, 0, data_ov001_020a0508->eventCount * sizeof(StageEvent));
    func_01ff8830(data_ov001_020a0508->bufferA, 0, sizeof(data_ov001_020a0508->bufferA));
    func_01ff8830(data_ov001_020a0508->bufferB, 0, sizeof(data_ov001_020a0508->bufferB));
    func_01ff8830(data_ov001_020a0508->bufferC, 0, sizeof(data_ov001_020a0508->bufferC));
    if (data_ov001_020a0508->linkFlags != 0) {
        func_01ff8830(data_ov001_020a0508->linkFlags, 0, data_ov001_020a0508->linkCount * sizeof(u32));
    }
    if (data_ov001_020a0508->links != 0) {
        func_01ff8830(data_ov001_020a0508->links, 0, data_ov001_020a0508->linkCount * sizeof(StageLink));
    }
    data_ov001_020a0508->pendingA = 0;
    data_ov001_020a0508->pendingB = 0;
    data_ov001_020a0508->activeLinks = 0;
    data_ov001_020a0508->pendingFlags = 0;
}
