#include "nitro/types.h"

typedef struct {
    u8 data[0x14];
} HeapRecord;

typedef struct {
    void *objectBlock;
    HeapRecord objectRecord;
    void *objectHeap;
    void *block;
    HeapRecord record;
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct {
    u8 data[0x1c8];
} StageEvent;

typedef struct {
    u8 data[0x124];
} StageObject;

typedef struct {
    u8 data[0x3c8];
} StageActor;

typedef struct {
    u8 data[0x1c];
} StageSlot;

typedef struct {
    u8 data[0x34];
} StageLinkNode;

typedef struct {
    u8 data[0xa4];
} StageTrigger;

typedef struct {
    u8 data[0x40];
} StageBufferA;

typedef struct {
    u8 data[0x30];
} StageBufferB;

typedef struct {
    u8 pad_00000[0x210];
    StageEvent *events;
    StageObject objects[64];
    StageActor actors[64];
    StageSlot slots[64];
    StageLinkNode linkNodes[64];
    StageTrigger triggers[64];
    StageBufferA buffersA[32];
    StageBufferB buffersB[32];
    u8 pad_18814[0x18d7c - 0x18814];
    void *eventPool;
    void *pools[8];
    u8 pad_18da0[0x18de4 - 0x18da0];
    u16 eventCount;
    u8 pad_18de6[0x18dfc - 0x18de6];
    void *messageA;
    void *messageB;
    u8 pad_18e04[8];
    void *messageC;
    void *messageD;
    HeapScope heapScope;
} StageManager;

typedef struct {
    u32 objectHeapSize;
    u32 heapSize;
    u32 eventCount;
} StageConfig;

typedef void (*StageUpdateFunc)(void);

extern StageManager *g_stageManager_020a0508;
extern StageConfig data_ov001_020a0354[];
extern char data_ov001_020a03d4[];
extern char data_ov001_020a03e4[];
extern char data_ov001_020a03f4[];
extern char data_ov001_020a0404[];
extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void *CreateHeapRecord_0202a0b4(HeapRecord *record, void *block, u32 size);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, int kind, int flags);
extern void *func_0202a158(void);
extern void *SetDefaultHeap_0202a134(void *heap);
extern void *func_ov001_0208f038(void *items, u32 stride, u32 count, void (*release)(void *));
extern void func_ov001_020998ac(void *item);
extern void func_ov001_020998cc(void *item);
extern void func_ov001_02099acc(void);

static inline void PushStageHeap(void)
{
    StageManager *manager = g_stageManager_020a0508;

    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
        manager->heapScope.savedHeap = func_0202a158();
        SetDefaultHeap_0202a134(manager->heapScope.objectHeap);
    }
}

static inline void PopStageHeap(void)
{
    StageManager *manager = g_stageManager_020a0508;

    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
        SetDefaultHeap_0202a134(manager->heapScope.savedHeap);
        manager->heapScope.savedHeap = NULL;
    }
}

StageUpdateFunc CreateStageManager_02099628(s16 *params)
{
    StageManager *manager;
    int variant;
    u32 size;

    if (g_stageManager_020a0508 != NULL) {
        return NULL;
    }
    manager = NNSi_FndGetCurrentRootHeap_0202a764();
    g_stageManager_020a0508 = manager;
    if (params != NULL && *params == 400) {
        variant = 1;
    } else {
        variant = 0;
    }
    size = data_ov001_020a0354[variant].objectHeapSize;
    manager->heapScope.objectBlock = NNSi_FndAllocFromDefaultHeap_0202a178(size);
    func_01ff8830(&manager->heapScope.objectRecord, 0, sizeof(HeapRecord));
    manager->heapScope.objectHeap = CreateHeapRecord_0202a0b4(&manager->heapScope.objectRecord, manager->heapScope.objectBlock, size);
    size = data_ov001_020a0354[variant].heapSize;
    manager->heapScope.block = NNSi_FndAllocFromDefaultHeap_0202a178(size);
    func_01ff8830(&manager->heapScope.record, 0, sizeof(HeapRecord));
    manager->heapScope.heap = CreateHeapRecord_0202a0b4(&manager->heapScope.record, manager->heapScope.block, size);
    g_stageManager_020a0508->eventCount = data_ov001_020a0354[variant].eventCount;
    g_stageManager_020a0508->events = NNSi_FndAllocFromDefaultHeap_0202a178(g_stageManager_020a0508->eventCount * sizeof(StageEvent));
    func_01ff88c4(g_stageManager_020a0508->events, 0, g_stageManager_020a0508->eventCount * sizeof(StageEvent));
    if (manager->messageA == NULL) {
        manager->messageA = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_020a03d4, 0xb, 0);
    }
    if (manager->messageB == NULL) {
        manager->messageB = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_020a03e4, 0xb, 0);
    }
    if (manager->messageC == NULL) {
        manager->messageC = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_020a03f4, 0xb, 0);
    }
    if (manager->messageD == NULL) {
        manager->messageD = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_020a0404, 0xb, 0);
    }
    PushStageHeap();
    manager->eventPool = func_ov001_0208f038(manager->events, sizeof(StageEvent), g_stageManager_020a0508->eventCount, NULL);
    manager->pools[0] = func_ov001_0208f038(manager->objects, sizeof(StageObject), 64, NULL);
    manager->pools[1] = func_ov001_0208f038(manager->actors, sizeof(StageActor), 64, func_ov001_020998ac);
    manager->pools[2] = func_ov001_0208f038(manager->slots, sizeof(StageSlot), 64, func_ov001_020998cc);
    manager->pools[4] = func_ov001_0208f038(manager->linkNodes, sizeof(StageLinkNode), 64, NULL);
    manager->pools[5] = func_ov001_0208f038(manager->triggers, sizeof(StageTrigger), 64, NULL);
    manager->pools[6] = func_ov001_0208f038(manager->buffersA, sizeof(StageBufferA), 32, NULL);
    manager->pools[7] = func_ov001_0208f038(manager->buffersB, sizeof(StageBufferB), 32, NULL);
    PopStageHeap();
    return func_ov001_02099acc;
}
