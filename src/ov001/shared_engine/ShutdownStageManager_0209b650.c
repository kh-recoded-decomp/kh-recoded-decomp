#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    void *objectHeap;
    u8 pad_1c[0x18];
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct {
    u32 unk_00;
    void *block;
} StageBuffer;

typedef struct {
    u8 pad_00[9];
    u8 unk_09_0 : 4;
    u8 marked : 1;
    u8 unk_09_5 : 3;
    u8 pad_0a[0x28 - 0xa];
} StageLink;

typedef struct {
    u8 pad_000[0x10];
    u16 id;
    u8 pad_012[0x1c8 - 0x12];
} StageEvent;

typedef struct {
    u8 pad_000[0x27c];
    u16 active;
    u8 pad_27e[0x3c8 - 0x27e];
} StageActor;

typedef struct {
    u8 pad_00[0xc];
    u16 active;
    u8 pad_0e[0x1c - 0xe];
} StageSlot;

typedef struct {
    void *model;
    void *buffer;
    u8 pad_08[4];
    u8 resource[0x80 - 0xc];
    void *resourceData;
} StageObjectRecord;

typedef struct {
    u32 flags;
    u8 pad_00004[4];
    StageBuffer buffers[64];
    StageLink *links;
    u32 *linkFlags;
    StageEvent *events;
    u8 pad_00214[0x4b14 - 0x214];
    StageActor actors[64];
    StageSlot slots[64];
    u8 pad_14414[0x18d80 - 0x14414];
    void *pools[8];
    u8 pad_18da0[0x18de4 - 0x18da0];
    u16 eventCount;
    u16 linkCount;
    u16 activeLinks;
    u16 pendingA;
    u16 pendingB;
    u8 pad_18dee[4];
    u16 pendingC;
    u8 pad_18df4[0x18e14 - 0x18df4];
    HeapScope heapScope;
    u8 pad_18e50[0x18e5c - 0x18e50];
    u32 pendingFlags;
} StageManager;

extern StageManager *g_stageManager_020a0508;
extern BOOL Session_Exists_0206c768(void);
extern void RemoveTaggedListEntries_0206c720(void (*callback)(void));
extern void func_ov001_02099a84(void);
extern void ReleaseSlotActor_02098360(StageSlot *slot);
extern void func_ov001_02093e54(StageEvent *event);
extern void ReleaseActorResources_02090240(StageActor *actor);
extern StageObjectRecord *GetStageObjectRecord_0209c0a0(u16 id);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ReleaseResourceAndDetach_0202eee8(void *resource);
extern void ZeroHalfThenFree_0202cd78(void *model);
extern void *func_0202a158(void);
extern void *SetDefaultHeap_0202a134(void *heap);
extern void HandlePool_ReleaseAll_0208f21c(void *pool);

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

void ShutdownStageManager_0209b650(void)
{
    int i;
    StageObjectRecord *record;

    if (Session_Exists_0206c768() && (g_stageManager_020a0508->flags & 0x80000000)) {
        RemoveTaggedListEntries_0206c720(func_ov001_02099a84);
    }
    g_stageManager_020a0508->flags &= 0x7fffffff;
    for (i = 0; i < 64; i++) {
        if (g_stageManager_020a0508->slots[i].active != 0) {
            ReleaseSlotActor_02098360(&g_stageManager_020a0508->slots[i]);
        }
    }
    for (i = 0; i < g_stageManager_020a0508->eventCount; i++) {
        if (g_stageManager_020a0508->events[i].id != 0) {
            func_ov001_02093e54(&g_stageManager_020a0508->events[i]);
        }
    }
    for (i = 0; i < 64; i++) {
        if (g_stageManager_020a0508->actors[i].active != 0) {
            ReleaseActorResources_02090240(&g_stageManager_020a0508->actors[i]);
        }
    }
    for (i = 0; i < 64; i++) {
        record = GetStageObjectRecord_0209c0a0(i + 1);
        if (record != NULL) {
            if (record->buffer != NULL) {
                NNSi_FndFreeFromDefaultHeap_0202a1c4(record->buffer);
                record->buffer = NULL;
            }
            if (record->resourceData != NULL) {
                ReleaseResourceAndDetach_0202eee8(record->resource);
            }
            if (record->model != NULL) {
                ZeroHalfThenFree_0202cd78(record->model);
                record->model = NULL;
            }
        }
    }
    g_stageManager_020a0508->pendingA = 0;
    PushStageHeap();
    for (i = 0; i < 64; i++) {
        if (g_stageManager_020a0508->buffers[i].block != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(g_stageManager_020a0508->buffers[i].block);
            g_stageManager_020a0508->buffers[i].block = NULL;
        }
    }
    g_stageManager_020a0508->pendingB = 0;
    PopStageHeap();
    g_stageManager_020a0508->pendingFlags = 0;
    if (g_stageManager_020a0508->links != NULL) {
        for (i = 0; i < g_stageManager_020a0508->linkCount; i++) {
            g_stageManager_020a0508->links[i].marked = 0;
        }
    }
    g_stageManager_020a0508->pendingC = 0;
    PushStageHeap();
    HandlePool_ReleaseAll_0208f21c(g_stageManager_020a0508->pools[0]);
    HandlePool_ReleaseAll_0208f21c(g_stageManager_020a0508->pools[1]);
    HandlePool_ReleaseAll_0208f21c(g_stageManager_020a0508->pools[2]);
    HandlePool_ReleaseAll_0208f21c(g_stageManager_020a0508->pools[4]);
    HandlePool_ReleaseAll_0208f21c(g_stageManager_020a0508->pools[5]);
    HandlePool_ReleaseAll_0208f21c(g_stageManager_020a0508->pools[6]);
    HandlePool_ReleaseAll_0208f21c(g_stageManager_020a0508->pools[7]);
    PopStageHeap();
}


