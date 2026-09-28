#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    void *slotPair1;
    void *slotPair1Aux;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record slot pair 1. */
void FreeRecordSlotPair1_02051b10(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->slotPair1);
    func_0202a1c4(manager->slotPair1Aux);
    manager->slotPair1 = 0;
    manager->slotPair1Aux = 0;
}
