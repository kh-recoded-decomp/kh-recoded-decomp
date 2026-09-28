#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x08];
    void *slotPair0;
    void *slotPair0Aux;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record slot pair 0. */
void FreeRecordSlotPair0_02051af0(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->slotPair0);
    func_0202a1c4(manager->slotPair0Aux);
    manager->slotPair0 = 0;
    manager->slotPair0Aux = 0;
}
