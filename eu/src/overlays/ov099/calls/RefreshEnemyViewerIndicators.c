#include "src/overlays/ov099/EnemyViewerState.h"

extern EnemyDrop *GetRecordSlot5Entry(int recordId);
extern BOOL IsEntryFlagSet_020c16ac(int flagSet, int enemyId);
extern void SetEntryFlag_020c16d4(int flagSet, int enemyId);
extern void SetGlobalPackedBit(int bitIndex);
extern void SetSlotObjVisible(int screen, int slot, int visible, EnemyViewer *viewer);
extern void RefreshSlotObj(int screen, int slot, u32 value, EnemyViewer *viewer);

static inline BOOL DropsComplete(EnemyViewer *viewer, int enemyId)
{
    return viewer->progress[enemyId].dropsComplete;
}

#pragma opt_propagation off
void RefreshEnemyViewerIndicators(EnemyViewer *viewer)
{
    EnemyListState *list = &viewer->list;
    EnemyDrop *drops = GetRecordSlot5Entry(viewer->selectedEnemy);
    int selectedEnemy = viewer->selectedEnemy;
    int row;

    viewer->selectedDrops = drops;
    if (IsEntryFlagSet_020c16ac(1, selectedEnemy)) {
        SetEntryFlag_020c16d4(2, selectedEnemy);
        SetGlobalPackedBit(0x1222 + selectedEnemy);
    }
    for (row = 0; row < list->pageSize; row++) {
        int firstEnemy = list->scrollTop;
        BOOL isNew = IsEntryFlagSet_020c16ac(1, firstEnemy + row);
        BOOL acknowledged = IsEntryFlagSet_020c16ac(2, firstEnemy + row) != 0;

        SetSlotObjVisible(0, row + 12, isNew, viewer);
        RefreshSlotObj(0, row + 12, acknowledged, viewer);
    }
    for (row = 0; row < list->pageSize; row++) {
        SetSlotObjVisible(0, row + 3,
            DropsComplete(viewer, list->scrollTop + row), viewer);
    }
}
