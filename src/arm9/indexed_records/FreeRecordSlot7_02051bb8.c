#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x38];
    void *slot7;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record slot 7. */
void FreeRecordSlot7_02051bb8(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->slot7);
    manager->slot7 = 0;
}
