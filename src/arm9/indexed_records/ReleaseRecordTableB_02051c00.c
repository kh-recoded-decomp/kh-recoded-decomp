#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x54];
    void *tableB;
    void *tableBAux;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record table B. */
void ReleaseRecordTableB_02051c00(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->tableB);
    func_0202a1c4(manager->tableBAux);
    manager->tableB = 0;
    manager->tableBAux = 0;
}
