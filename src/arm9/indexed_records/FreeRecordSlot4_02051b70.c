#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    void *slot4;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record slot 4. */
void FreeRecordSlot4_02051b70(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->slot4);
    manager->slot4 = 0;
}
