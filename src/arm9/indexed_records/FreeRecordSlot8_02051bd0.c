#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    void *slot8;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record slot 8. */
void FreeRecordSlot8_02051bd0(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->slot8);
    manager->slot8 = 0;
}
