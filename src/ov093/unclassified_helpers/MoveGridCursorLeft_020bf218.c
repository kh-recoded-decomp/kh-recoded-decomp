#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    int pageIndex;
    int pageOffset;
} PageState;

typedef struct {
    u8 pad_0000[0xcaa8];
    int unk_CAA8;
    u8 pad_caac[0xcf4c - 0xcaac];
    int selectedIndex;
    int isClosing;
    PageState pager;
    u8 pad_cf88[0xd1c4 - 0xcf88];
    int isLocked;
    u8 pad_d1c8[0xd21c - 0xd1c8];
    int unk_D21C;
} SceneWork;

extern SceneWork *g_sceneWork_020c50e0;
extern u16 data_02060500;

extern int func_ov093_020c2348(void);
extern BOOL IsEntryFlagSet_020c22a4(int flagSet, int entryIndex);
extern void SetEntryFlag_020c22d4(int flagSet, int entryIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void func_ov093_020c0564(int side, int slotIndex, BOOL enabled, SceneWork *work);
extern void func_ov093_020c0458(int side, int layer, int offset, int value, SceneWork *work);
extern void func_ov093_020bfd60(int mode, SceneWork *work);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern BOOL func_ov093_020c0bec(int mode, SceneWork *work);
extern void ResetSmoothValue_020c2058(int index);
extern void func_ov093_020c05b8(SceneWork *work);

void MoveGridCursorLeft_020bf218(SceneWork *work)
{
    PageState *pager;
    int entryIndex;
    int column;
    int page;

    if (func_ov093_020c2348() != 6) {
        return;
    }
    if (work->isClosing == 0 && work->isLocked == 0) {
        pager = &work->pager;
        column = work->selectedIndex % 5 - 1;
        page = pager->pageIndex + pager->pageOffset;
        if (column < 0 && (data_02060500 & 0x20) != 0) {
            column = 4;
        }
        if (column < 0) {
            return;
        }
        entryIndex = column + page * 5;
        work->selectedIndex = entryIndex;
        if (IsEntryFlagSet_020c22a4(4, entryIndex)) {
            SetEntryFlag_020c22d4(5, entryIndex);
            SetGlobalPackedBit_02027320(entryIndex + 0x1202);
        }
        for (entryIndex = 0; entryIndex < 10; entryIndex++) {
            func_ov093_020c0564(0, entryIndex + 3, IsEntryFlagSet_020c22a4(5, entryIndex + pager->pageIndex * 5) != 0, work);
        }
        func_ov093_020c0458(0, 2, (column + 1) * 0x2c, work->unk_CAA8, work);
        func_ov093_020bfd60(0, work);
        PlaySoundEffect_0204d924(0, 0);
    } else {
        if (!func_ov093_020c0bec(1, work)) {
            return;
        }
        ResetSmoothValue_020c2058(0);
        g_sceneWork_020c50e0->unk_D21C = 0;
        if (work->isLocked == 0) {
            PlaySoundEffect_0204d924(0, 0);
        }
        func_ov093_020bfd60(1, work);
        func_ov093_020c05b8(work);
    }
}




