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
extern const char data_02056198[];
extern const char data_020561a4[];
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, int size);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);

BOOL AcquireRecordManager_02051c80(void)
{
    RecordManager *manager;

    if (g_recordManager_020613d0 != NULL) {
        g_recordManager_020613d0->useCount++;
        return TRUE;
    }
    manager = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(RecordManager));
    g_recordManager_020613d0 = manager;
    func_01ff8830(manager, 0, sizeof(RecordManager));
    manager->useCount = 1;
    manager->containerA = Msg_OpenContainerAndReadHeader_0202cc6c(data_02056198, 0x11, FALSE);
    manager->containerB = Msg_OpenContainerAndReadHeader_0202cc6c(data_020561a4, 0x11, FALSE);
    return TRUE;
}
