#include "src/overlays/ov099/EnemyViewerInfo.h"

typedef struct EnemyDrop {
    s16 itemId;
    u8 bonus;
    u8 extra;
    u16 chance;
} EnemyDrop;

typedef struct EnemyDropIds {
    s32 itemId[4];
} EnemyDropIds;

typedef struct EnemyProgress {
    s32 defeatCount;
    BOOL dropsComplete;
} EnemyProgress;

typedef struct EnemyViewer {
    u8 unknown0000[0xcf10];
    EnemyProgress progress[40];
} EnemyViewer;

typedef char EnemyDropSize[sizeof(EnemyDrop) == 6 ? 1 : -1];
typedef char EnemyProgressSize[sizeof(EnemyProgress) == 8 ? 1 : -1];

extern EnemyDrop *GetRecordSlot5Entry(int recordId);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);

#pragma opt_scalarize off
void LoadEnemyCollectionProgress(EnemyViewer *viewer)
{
    int enemyId;

    for (enemyId = 0; enemyId < 40; enemyId++) {
        EnemyProgress *progress = &viewer->progress[enemyId];
        EnemyDrop *drops = GetRecordSlot5Entry(enemyId);
        EnemyDropIds ids = {{drops[0].itemId, drops[1].itemId,
                            drops[2].itemId, drops[3].itemId}};

        progress->defeatCount = ReadGlobalPackedBits(
            gEnemyViewerEntryInfo[enemyId].defeatCountBitOffset, 17);
        progress->dropsComplete = FALSE;
        if (ids.itemId[0] == -1) {
            if (progress->defeatCount > 0) {
                progress->dropsComplete = TRUE;
            }
        } else {
            if (ReadGlobalPackedBits(0x5c0 + enemyId * 4, 4) == 0xf) {
                progress->dropsComplete = TRUE;
            }
        }
    }
}
