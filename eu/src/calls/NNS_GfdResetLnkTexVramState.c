#include "nitro/types.h"

typedef struct LnkVramBlock LnkVramBlock;

typedef struct {
    LnkVramBlock *usedList;
    LnkVramBlock *usedListFor4x4;
    LnkVramBlock *blockPool;
    u32 szByte;
    u32 szByteFor4x4;
    void *workHead;
    u32 szByteWork;
} LnkTexVramManager;

typedef struct {
    u32 szFree;
    u32 szNormal;
    u32 sz4x4;
} VramSlot;

typedef struct {
    VramSlot slot[4];
} VramSlotTable;

extern LnkTexVramManager sLnkTexVramManager;
extern LnkVramBlock *sLnkTexUsedList;
extern LnkVramBlock *sLnkTexCompressedUsedList;
extern LnkVramBlock *sLnkTexBlockPool;
extern const VramSlotTable sLnkTexInitialSlots;

extern void NNSi_GfdInitLnkVramMan(LnkVramBlock **listHead);
extern LnkVramBlock *NNSi_GfdInitLnkVramBlockPool(void *work, u32 count);
extern BOOL NNSi_GfdAddNewFreeBlock(LnkVramBlock **usedListHead, LnkVramBlock **freeListHead, u32 start, u32 size);
extern void NNSi_GfdMergeAllFreeBlocks(LnkVramBlock **usedListHead, LnkVramBlock **freeListHead);

void NNS_GfdResetLnkTexVramState(void)
{
    VramSlotTable table = sLnkTexInitialSlots;
    u32 szNormal = sLnkTexVramManager.szByte
                 - (sLnkTexVramManager.szByteFor4x4 + (sLnkTexVramManager.szByteFor4x4 >> 1));
    u32 sz4x4 = sLnkTexVramManager.szByteFor4x4;
    u32 szPltt = sLnkTexVramManager.szByteFor4x4 >> 1;
    u32 i;
    u32 size;

    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 2) {
            if (table.slot[i].szFree != 0 && sz4x4 != 0) {
                size = table.slot[i].szFree;
                if (size > sz4x4) {
                    size = sz4x4;
                }
                table.slot[i].sz4x4 += size;
                sz4x4 -= size;
                table.slot[i].szFree -= size;
            }
        }
    }

    table.slot[1].szFree -= szPltt;

    for (i = 0; i < 4; i++) {
        if (table.slot[i].szFree != 0 && szNormal != 0) {
            size = table.slot[i].szFree;
            if (size > szNormal) {
                size = szNormal;
            }
            table.slot[i].szNormal += size;
            szNormal -= size;
            table.slot[i].szFree -= size;
        }
    }

    NNSi_GfdInitLnkVramMan(&sLnkTexUsedList);
    NNSi_GfdInitLnkVramMan(&sLnkTexCompressedUsedList);
    sLnkTexVramManager.blockPool =
        NNSi_GfdInitLnkVramBlockPool(sLnkTexVramManager.workHead, sLnkTexVramManager.szByteWork >> 4);

    if (table.slot[0].sz4x4 != 0) {
        NNSi_GfdAddNewFreeBlock(&sLnkTexCompressedUsedList, &sLnkTexBlockPool, 0, table.slot[0].sz4x4);
    }
    if (table.slot[0].szNormal != 0) {
        NNSi_GfdAddNewFreeBlock(&sLnkTexUsedList, &sLnkTexBlockPool,
                                       table.slot[0].sz4x4, table.slot[0].szNormal);
    }
    if (table.slot[2].sz4x4 != 0) {
        NNSi_GfdAddNewFreeBlock(&sLnkTexCompressedUsedList, &sLnkTexBlockPool, 0x40000, table.slot[2].sz4x4);
    }
    if (table.slot[2].szNormal != 0) {
        NNSi_GfdAddNewFreeBlock(&sLnkTexUsedList, &sLnkTexBlockPool,
                                       0x40000 + table.slot[2].sz4x4, table.slot[2].szNormal);
    }
    if (table.slot[3].szNormal != 0) {
        NNSi_GfdAddNewFreeBlock(&sLnkTexUsedList, &sLnkTexBlockPool, 0x60000, table.slot[3].szNormal);
    }
    if (table.slot[1].szNormal != 0) {
        NNSi_GfdAddNewFreeBlock(&sLnkTexUsedList, &sLnkTexBlockPool, 0x20000 + szPltt, table.slot[1].szNormal);
    }

    NNSi_GfdMergeAllFreeBlocks(&sLnkTexUsedList, &sLnkTexBlockPool);
    NNSi_GfdMergeAllFreeBlocks(&sLnkTexCompressedUsedList, &sLnkTexBlockPool);
}
