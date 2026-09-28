#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x5c];
    void *tableC;
    void *tableCAux;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record table C. */
void ReleaseRecordTableC_02051c20(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->tableC);
    func_0202a1c4(manager->tableCAux);
    manager->tableC = 0;
    manager->tableCAux = 0;
}
