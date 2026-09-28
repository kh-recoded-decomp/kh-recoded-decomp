#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    void *slotPair3;
    void *slotPair3Aux;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record slot pair 3. */
void FreeRecordSlotPair3_02051b50(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->slotPair3);
    func_0202a1c4(manager->slotPair3Aux);
    manager->slotPair3 = 0;
    manager->slotPair3Aux = 0;
}
