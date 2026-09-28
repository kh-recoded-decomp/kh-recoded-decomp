#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    void *tableA;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record table A. */
void ReleaseRecordTableA_02051be8(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->tableA);
    manager->tableA = 0;
}
