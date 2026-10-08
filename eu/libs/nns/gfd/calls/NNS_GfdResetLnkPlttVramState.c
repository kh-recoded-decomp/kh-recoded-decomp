#include "nitro/types.h"

typedef struct {
    void *usedListHead;
    void *freeListHead;
    u32 param1;
    u32 bufferBase;
    u32 bufferSize;
} TableManagerFields;

extern TableManagerFields sLnkPlttVramManager;
extern void *sLnkPlttVramManagerListHead;
extern void *sLnkPlttVramBlockPoolList;

extern void *NNSi_GfdInitLnkVramBlockPool(void *nodes, u32 count);
extern void NNSi_GfdInitLnkVramMan(u32 manager);
extern void NNSi_GfdAddNewFreeBlock(
    void *usedListHeadPtr,
    void *freeListHeadPtr,
    u32 address,
    u32 size
);
extern void NNSi_GfdMergeAllFreeBlocks(void *usedListHeadPtr, void *freeListHeadPtr);

void NNS_GfdResetLnkPlttVramState(void)
{
    sLnkPlttVramManager.freeListHead = NNSi_GfdInitLnkVramBlockPool(
        (void *)sLnkPlttVramManager.bufferBase,
        sLnkPlttVramManager.bufferSize >> 4
    );
    NNSi_GfdInitLnkVramMan((u32)&sLnkPlttVramManagerListHead);
    NNSi_GfdAddNewFreeBlock(
        &sLnkPlttVramManagerListHead,
        &sLnkPlttVramBlockPoolList,
        0,
        sLnkPlttVramManager.param1
    );
    NNSi_GfdMergeAllFreeBlocks(
        &sLnkPlttVramManagerListHead,
        &sLnkPlttVramBlockPoolList
    );
}
