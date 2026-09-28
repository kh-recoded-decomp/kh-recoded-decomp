#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x30];
    void *slot5;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record slot 5. */
void FreeRecordSlot5_02051b88(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->slot5);
    manager->slot5 = 0;
}
