#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x34];
    void *slot6;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record slot 6. */
void FreeRecordSlot6_02051ba0(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->slot6);
    manager->slot6 = 0;
}
