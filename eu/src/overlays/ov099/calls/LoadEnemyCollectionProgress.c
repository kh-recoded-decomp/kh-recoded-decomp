#include "src/overlays/ov099/EnemyViewerInfo.h"
#include "src/overlays/ov099/EnemyViewerState.h"

typedef struct EnemyDropIds {
    s32 itemId[4];
} EnemyDropIds;

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
