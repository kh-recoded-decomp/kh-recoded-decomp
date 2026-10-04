#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    int pageIndex;
    int pageOffset;
} PageState;

typedef struct {
    u8 pad_0000[0xcf4c];
    int selectedIndex;
    int isClosing;
    PageState pager;
    u8 pad_cf88[0xd1c4 - 0xcf88];
    int isLocked;
    u8 pad_d1c8[0xd21c - 0xd1c8];
    int unk_D21C;
} SceneWork;

extern SceneWork *g_sceneWork_020c50e0;

extern int func_ov093_020c2348(void);
extern BOOL IsEntryFlagSet_020c22a4(int flagSet, int entryIndex);
extern void SetEntryFlag_020c22d4(int flagSet, int entryIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void SetSlotAnimFlag_020c0310(int side, int slotIndex, int value, SceneWork *work);
extern void func_ov093_020c0564(int side, int slotIndex, BOOL enabled, SceneWork *work);
extern void func_ov093_020bfd60(int mode, SceneWork *work);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern BOOL func_ov093_020c0a9c(int mode, SceneWork *work);
extern void ResetSmoothValue_020c2058(int index);
extern void func_ov093_020c05b8(SceneWork *work);

void FinishGridPageScrollDual_020bf028(SceneWork *work)
{
    PageState *pager;
    int entryIndex;
    int i;
    int unlocked;
    BOOL seen;
    u32 scroll;

    if (func_ov093_020c2348() != 6) {
        return;
    }
    if (work->isClosing == 0 && work->isLocked == 0) {
        if (!func_ov093_020c0a9c(0, work)) {
            return;
        }
        ResetSmoothValue_020c2058(0);
        g_sceneWork_020c50e0->unk_D21C = 0;
        pager = &work->pager;
        entryIndex = work->selectedIndex % 5 + (pager->pageIndex + pager->pageOffset) * 5;
        work->selectedIndex = entryIndex;
        if (IsEntryFlagSet_020c22a4(4, entryIndex)) {
            SetEntryFlag_020c22d4(5, entryIndex);
            SetGlobalPackedBit_02027320(entryIndex + 0x1202);
        }
        for (i = 0; i < 10; i++) {
            entryIndex = pager->pageIndex * 5;
            unlocked = IsEntryFlagSet_020c22a4(4, i + entryIndex);
            seen = IsEntryFlagSet_020c22a4(5, i + entryIndex) != 0;
            SetSlotAnimFlag_020c0310(0, i + 3, unlocked, work);
            func_ov093_020c0564(0, i + 3, seen, work);
        }
        PlaySoundEffect_0204d924(0, 0);
        func_ov093_020bfd60(0, work);
        scroll = ((u32)(work->pager.pageIndex * 48) << 16) & 0x01ff0000;
        *(vu32 *)0x0400001c = scroll;
        *(vu32 *)0x04000010 = scroll;
    } else {
        if (!func_ov093_020c0a9c(1, work)) {
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



