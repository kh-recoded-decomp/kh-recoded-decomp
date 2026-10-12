#ifndef KH_RECODED_STAGE_MANAGER_MEMORY_H
#define KH_RECODED_STAGE_MANAGER_MEMORY_H

#include "src/HeapRecord.h"

typedef struct StageHeapBlock {
    void *memory;
    HeapRecord record;
    HeapRecord *activeRecord;
} StageHeapBlock;

typedef struct StageHeapScope {
    StageHeapBlock blocks[2];
    HeapRecord *savedHeap;
} StageHeapScope;

/* Resource-ownership view; actors and other intervening work have separate views. */
typedef struct StageManagerMemory {
    u32 flags;
    u8 reserved004[0x208 - 4];
    void *links;
    void *linkFlags;
    void *events;
    u8 reserved214[0x18d7c - 0x214];
    void *eventPool;
    void *pools[8];
    u8 reserved18da0[0x18dfc - 0x18da0];
    void *messageA;
    void *messageB;
    u8 reserved18e04[8];
    void *messageC;
    void *messageD;
    StageHeapScope heapScope;
} StageManagerMemory;

extern StageManagerMemory *gStageManager;
extern void DestroyStageManager(void);

typedef char StageHeapBlockSizeCheck[sizeof(StageHeapBlock) == 0x1c ? 1 : -1];
typedef char StageHeapScopeSizeCheck[sizeof(StageHeapScope) == 0x3c ? 1 : -1];
typedef char StageEventsOffsetCheck[
    (u32)&((StageManagerMemory *)0)->events == 0x210 ? 1 : -1];
typedef char StageEventPoolOffsetCheck[
    (u32)&((StageManagerMemory *)0)->eventPool == 0x18d7c ? 1 : -1];
typedef char StageMessagesOffsetCheck[
    (u32)&((StageManagerMemory *)0)->messageA == 0x18dfc ? 1 : -1];
typedef char StageHeapScopeOffsetCheck[
    (u32)&((StageManagerMemory *)0)->heapScope == 0x18e14 ? 1 : -1];

#endif
