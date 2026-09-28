#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    s32 scrollRow;
    u8 pad_30[0x1c];
} ScrollList;

typedef struct {
    s32 selectedEntry;
    BOOL unk_04;
    u8 pad_008[0x180 - 0x8];
    ScrollList lists[2];
    u8 pad_218[0xf064 - 0x218];
    BOOL isTouchScrolling;
    s32 scrollOffsetY;
    u8 pad_f06c[0xf0c4 - 0xf06c];
    BOOL isScrollEasing;
} MenuScene;

extern MenuScene *g_menuScene_020c2520;
extern BOOL ScrollListForward_020c0850(int listIndex, MenuScene *scene);
extern void ResetScrollTrack_020c1228(int trackIndex);
extern void RefreshListPanels_020bfb38(int listIndex, MenuScene *scene);
extern BOOL IsEntryFlagSet_020c1474(int flagSet, int entryIndex);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void ScrollEntryListDown_020bf2f4(MenuScene *scene)
{
    s32 selectedEntry;

    if (!scene->unk_04 && !scene->isTouchScrolling) {
        return;
    }
    if (!ScrollListForward_020c0850(1, scene)) {
        return;
    }
    scene->scrollOffsetY = scene->lists[1].scrollRow * -16;
    selectedEntry = scene->selectedEntry;
    ResetScrollTrack_020c1228(1);
    g_menuScene_020c2520->isScrollEasing = FALSE;
    RefreshListPanels_020bfb38(1, scene);
    if (IsEntryFlagSet_020c1474(0, selectedEntry) && !scene->isTouchScrolling) {
        PlaySoundEffect_0204d924(0, 0);
    }
}
