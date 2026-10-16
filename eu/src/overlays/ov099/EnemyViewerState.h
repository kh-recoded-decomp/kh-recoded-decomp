#ifndef RECODED_ENEMY_VIEWER_STATE_H
#define RECODED_ENEMY_VIEWER_STATE_H

#include "nitro/types.h"

typedef struct EnemyDrop {
    s16 itemId;
    u8 bonus;
    u8 extra;
    u16 chance;
} EnemyDrop;

typedef struct EnemyProgress {
    s32 defeatCount;
    BOOL dropsComplete;
} EnemyProgress;

typedef struct EnemyListState {
    int screen;
    int pageSize;
    u8 unknown08[0x2c - 8];
    int scrollTop;
} EnemyListState;

typedef struct EnemyViewer {
    u8 unknown0000[0xcf04];
    int selectedEnemy;
    u8 unknowncf08[8];
    EnemyProgress progress[40];
    EnemyDrop *selectedDrops;
    EnemyListState list;
} EnemyViewer;

typedef char EnemyDropSize[sizeof(EnemyDrop) == 6 ? 1 : -1];
typedef char EnemyProgressSize[sizeof(EnemyProgress) == 8 ? 1 : -1];
typedef char EnemyViewerProgressOffset[(u32)&((EnemyViewer *)0)->progress == 0xcf10 ? 1 : -1];
typedef char EnemyViewerDropPointerOffset[(u32)&((EnemyViewer *)0)->selectedDrops == 0xd050 ? 1 : -1];
typedef char EnemyViewerListOffset[(u32)&((EnemyViewer *)0)->list == 0xd054 ? 1 : -1];

#endif
