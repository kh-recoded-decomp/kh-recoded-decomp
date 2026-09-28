#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    void *slotPair2;
    void *slotPair2Aux;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;
extern void func_0202a1c4(void *block);

/* Frees and clears record slot pair 2. */
void FreeRecordSlotPair2_02051b30(void)
{
    RecordManager *manager = g_recordManager_020613d0;

    func_0202a1c4(manager->slotPair2);
    func_0202a1c4(manager->slotPair2Aux);
    manager->slotPair2 = 0;
    manager->slotPair2Aux = 0;
}
