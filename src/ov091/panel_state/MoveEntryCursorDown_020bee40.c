#include "nitro/types.h"

typedef struct {
    int id;
    int visibleRows;
    int totalRows;
    int panelIndex;
    u8 pad_10[0x1c];
    int topRow;
    int cursorRow;
    u8 pad_34[0x18];
} ScrollList;

typedef struct {
    int selectedEntry;
    u8 pad_04[0xcbcc];
    ScrollList lists[1];
} MenuScene;

extern BOOL func_ov091_020c1754(void);
extern BOOL ScrollListDown_020c0010(int listIndex, MenuScene *scene);
extern BOOL IsEntryFlagSet_020c16e8(int flagSet, int entryIndex);
extern void SetEntryFlag_020c1718(int flagSet, int entryIndex);
extern void SetListPanelSlotValue_020bfbac(int screen, int panelIndex, int value, MenuScene *scene);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void MoveEntryCursorDown_020bee40(MenuScene *scene)
{
    ScrollList *list;
    int entry;

    if (func_ov091_020c1754()) {
        return;
    }
    if (!ScrollListDown_020c0010(0, scene)) {
        return;
    }
    list = &scene->lists[0];
    entry = list->topRow + list->cursorRow;
    scene->selectedEntry = entry;
    if (IsEntryFlagSet_020c16e8(2, entry)) {
        SetEntryFlag_020c1718(3, entry);
    }
    entry = scene->selectedEntry;
    SetListPanelSlotValue_020bfbac(0, entry + 1, IsEntryFlagSet_020c16e8(3, entry) ? TRUE : FALSE, scene);
    PlaySoundEffect_0204d924(0, 0);
}
