#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x64];
    void *tableD;
    void *tableDAux1;
    void *tableDAux2;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record table D. */
void ReleaseRecordTableD_02051c40(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->tableD);
    func_0202a1c4(manager->tableDAux1);
    func_0202a1c4(manager->tableDAux2);
    manager->tableD = 0;
    manager->tableDAux1 = 0;
    manager->tableDAux2 = 0;
}
