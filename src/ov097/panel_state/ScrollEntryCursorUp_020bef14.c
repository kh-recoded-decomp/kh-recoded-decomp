#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    s32 scrollRow;
    s32 cursorRow;
    u8 pad_34[0x18];
} ScrollList;

typedef struct {
    u8 pad_000[0x3e8];
    int detailId;
    u8 pad_3ec[0x414 - 0x3ec];
} EntryLayout;

typedef struct {
    u32 values[2];
    int detailId;
    u32 rest[8];
} DetailRequest;

typedef struct {
    s32 selectedEntry;
    BOOL unk_04;
    u8 pad_008[0x180 - 0x8];
    ScrollList lists[2];
    u8 pad_218[0xce08 - 0x218];
    EntryLayout layouts[1];
    u8 pad_d21c[0xf064 - 0xd21c];
    BOOL isTouchScrolling;
    s32 scrollOffsetY;
    u8 pad_f06c[0xf0c4 - 0xf06c];
    BOOL isScrollEasing;
} MenuScene;

extern MenuScene *g_menuScene_020c2520;
extern DetailRequest data_ov097_020c1ef0;
extern BOOL StepListCursorUp_020c055c(int listIndex, MenuScene *scene);
extern void func_ov097_020c02f4(DetailRequest *request, MenuScene *scene);
extern void ResetScrollTrack_020c1228(int trackIndex);
extern void RefreshListPanels_020bfb38(int listIndex, MenuScene *scene);
extern BOOL IsEntryFlagSet_020c1474(int flagSet, int entryIndex);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov097_020c1558(int listIndex, MenuScene *scene);

void ScrollEntryCursorUp_020bef14(MenuScene *scene)
{
    DetailRequest request;
    s32 selectedEntry;
    int entryIndex;

    if (!scene->unk_04 && !scene->isTouchScrolling) {
        if (!StepListCursorUp_020c055c(0, scene)) {
            return;
        }
        entryIndex = scene->lists[0].scrollRow + scene->lists[0].cursorRow;
        scene->selectedEntry = entryIndex;
        request = data_ov097_020c1ef0;
        request.detailId = scene->layouts[entryIndex].detailId;
        func_ov097_020c02f4(&request, scene);
        ResetScrollTrack_020c1228(1);
        g_menuScene_020c2520->isScrollEasing = FALSE;
        ResetScrollTrack_020c1228(1);
        g_menuScene_020c2520->isScrollEasing = FALSE;
        scene->scrollOffsetY = 0;
        RefreshListPanels_020bfb38(1, scene);
        PlaySoundEffect_0204d924(0, 0);
        func_ov097_020c1558(1, scene);
        return;
    }
    if (!StepListCursorUp_020c055c(1, scene)) {
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
