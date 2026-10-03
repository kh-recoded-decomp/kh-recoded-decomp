#include "nitro/types.h"

typedef struct StageResource {
    u16 id;
    u16 pad_02;
    void *data;
} StageResource;

typedef struct {
    u8 pad_00[0x18];
    void *objectHeap;
    u8 pad_1c[0x18];
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct StageManager {
    u8 pad_00[0x08];
    StageResource resources[64];
    u8 pad_208[0x18dec - 0x208];
    u16 resourceCount;
    u8 pad_18dee[0x12];
    s32 archiveBase;
    u8 pad_18e04[0x10];
    HeapScope heapScope;
} StageManager;

extern StageManager *g_stageManager_020a0508;

extern u16 FindStageLinkIndex_02099544(u32 id);
extern u32 func_0202cb7c(u32 fileId);
extern void *func_0202a158(void);
extern void *SetDefaultHeap_0202a134(void *heap);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern u32 LoadFileIntoBuffer_0202c4a0(u32 fileId, void *buffer, u32 size);
extern void RelocateResourceTable_0208efcc(void *table);
extern void *GetStageEntry_0209c074(int id);

#define STAGE_FILE_ID(index) (0x80000000 | (((g_stageManager_020a0508->archiveBase + 0x8000) & 0xfffffc) << 7) | (index))

void *LoadStageResource_0209a784(u32 id)
{
    u16 slot = FindStageLinkIndex_02099544(id);
    StageManager *manager;
    u32 fileIndex;
    u32 size;
    void *buffer;

    if (slot == 0) {
        fileIndex = id & 0x1ff;
        size = func_0202cb7c(STAGE_FILE_ID(fileIndex));
        if (size == 0) {
            return NULL;
        }
        manager = g_stageManager_020a0508;
        if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
            manager->heapScope.savedHeap = func_0202a158();
            SetDefaultHeap_0202a134(manager->heapScope.objectHeap);
        }
        buffer = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, 0x20);
        if (buffer == NULL) {
            return NULL;
        }
        manager = g_stageManager_020a0508;
        if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
            SetDefaultHeap_0202a134(manager->heapScope.savedHeap);
            manager->heapScope.savedHeap = NULL;
        }
        if ((u16)LoadFileIntoBuffer_0202c4a0(STAGE_FILE_ID(fileIndex), buffer, size) == 0) {
            return NULL;
        }
        g_stageManager_020a0508->resources[g_stageManager_020a0508->resourceCount].id = id;
        g_stageManager_020a0508->resources[g_stageManager_020a0508->resourceCount].data = buffer;
        g_stageManager_020a0508->resourceCount++;
        RelocateResourceTable_0208efcc(buffer);
        slot = g_stageManager_020a0508->resourceCount;
    }
    return GetStageEntry_0209c074((s16)slot);
}
