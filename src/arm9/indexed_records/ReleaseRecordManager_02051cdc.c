#include "nitro/types.h"

typedef struct RecordManager {
    void *containerA;
    void *containerB;
    u8 pad_08[0x3c];
    u8 refCounts[14];
    u8 useCount;
    u8 pad_53[0x74 - 0x53];
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void ZeroHalfThenFree_0202cd78(void *container);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void ReleaseRecordManager_02051cdc(void)
{
    RecordManager *manager = g_recordManager_020613d0;
    int slot;

    if (manager == NULL) {
        return;
    }
    manager->useCount--;
    if (manager->useCount != 0) {
        return;
    }
    for (slot = 0; slot < 14; slot++) {
        if (manager->refCounts[slot] != 0) {
            manager->refCounts[slot] = 1;
            ReleaseRecordSlot_02051dfc(slot);
        }
    }
    ZeroHalfThenFree_0202cd78(manager->containerB);
    ZeroHalfThenFree_0202cd78(manager->containerA);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(manager);
    g_recordManager_020613d0 = NULL;
}
