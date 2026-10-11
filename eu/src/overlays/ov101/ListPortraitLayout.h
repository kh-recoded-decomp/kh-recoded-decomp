#ifndef OV101_LIST_PORTRAIT_LAYOUT_H
#define OV101_LIST_PORTRAIT_LAYOUT_H

#include "nitro/types.h"

typedef struct ListPortraitEntry {
    s32 fileIndex; /* -1 marks an unused slot. */
    s32 x;
    s32 y;
} ListPortraitEntry;

typedef struct ListPortraitLayout {
    ListPortraitEntry entries[30];
    s32 baseUnlockCount;
    s32 unlockBit;
} ListPortraitLayout;

typedef char ListPortraitLayoutMustBe368Bytes[
    sizeof(ListPortraitLayout) == 0x170 ? 1 : -1];

extern ListPortraitLayout gListPortraitLayouts[40];

#endif
