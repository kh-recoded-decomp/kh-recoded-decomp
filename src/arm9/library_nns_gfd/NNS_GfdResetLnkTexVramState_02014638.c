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

extern LnkTexVramManager g_lnkTexVramManager_0205a8e4;
extern LnkVramBlock *s_texUsedList_0205a8e4;
extern LnkVramBlock *s_tex4x4UsedList_0205a8e8;
extern LnkVramBlock *s_texBlockPool_0205a8ec;
extern const VramSlotTable s_vramSlotInit_02052f8c;

extern void NNSi_GfdInitLnkVramMan_020141dc(LnkVramBlock **listHead);
extern LnkVramBlock *NNSi_GfdInitLnkVramBlockPool_020141e8(void *work, u32 count);
extern BOOL LinkBlockFromFreeList_0201422c(LnkVramBlock **usedListHead, LnkVramBlock **freeListHead, u32 start, u32 size);
extern void MergeUsedBlocksIntoFreeList_020143d4(LnkVramBlock **usedListHead, LnkVramBlock **freeListHead);

void NNS_GfdResetLnkTexVramState_02014638(void)
{
    VramSlotTable table = s_vramSlotInit_02052f8c;
    u32 szNormal = g_lnkTexVramManager_0205a8e4.szByte
                 - (g_lnkTexVramManager_0205a8e4.szByteFor4x4 + (g_lnkTexVramManager_0205a8e4.szByteFor4x4 >> 1));
    u32 sz4x4 = g_lnkTexVramManager_0205a8e4.szByteFor4x4;
    u32 szPltt = g_lnkTexVramManager_0205a8e4.szByteFor4x4 >> 1;
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

    NNSi_GfdInitLnkVramMan_020141dc(&s_texUsedList_0205a8e4);
    NNSi_GfdInitLnkVramMan_020141dc(&s_tex4x4UsedList_0205a8e8);
    g_lnkTexVramManager_0205a8e4.blockPool =
        NNSi_GfdInitLnkVramBlockPool_020141e8(g_lnkTexVramManager_0205a8e4.workHead, g_lnkTexVramManager_0205a8e4.szByteWork >> 4);

    if (table.slot[0].sz4x4 != 0) {
        LinkBlockFromFreeList_0201422c(&s_tex4x4UsedList_0205a8e8, &s_texBlockPool_0205a8ec, 0, table.slot[0].sz4x4);
    }
    if (table.slot[0].szNormal != 0) {
        LinkBlockFromFreeList_0201422c(&s_texUsedList_0205a8e4, &s_texBlockPool_0205a8ec,
                                       table.slot[0].sz4x4, table.slot[0].szNormal);
    }
    if (table.slot[2].sz4x4 != 0) {
        LinkBlockFromFreeList_0201422c(&s_tex4x4UsedList_0205a8e8, &s_texBlockPool_0205a8ec, 0x40000, table.slot[2].sz4x4);
    }
    if (table.slot[2].szNormal != 0) {
        LinkBlockFromFreeList_0201422c(&s_texUsedList_0205a8e4, &s_texBlockPool_0205a8ec,
                                       0x40000 + table.slot[2].sz4x4, table.slot[2].szNormal);
    }
    if (table.slot[3].szNormal != 0) {
        LinkBlockFromFreeList_0201422c(&s_texUsedList_0205a8e4, &s_texBlockPool_0205a8ec, 0x60000, table.slot[3].szNormal);
    }
    if (table.slot[1].szNormal != 0) {
        LinkBlockFromFreeList_0201422c(&s_texUsedList_0205a8e4, &s_texBlockPool_0205a8ec, 0x20000 + szPltt, table.slot[1].szNormal);
    }

    MergeUsedBlocksIntoFreeList_020143d4(&s_texUsedList_0205a8e4, &s_texBlockPool_0205a8ec);
    MergeUsedBlocksIntoFreeList_020143d4(&s_tex4x4UsedList_0205a8e8, &s_texBlockPool_0205a8ec);
}
