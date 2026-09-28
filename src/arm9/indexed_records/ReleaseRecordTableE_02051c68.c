#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x70];
    void *tableE;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record table E. */
void ReleaseRecordTableE_02051c68(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->tableE);
    manager->tableE = 0;
}
