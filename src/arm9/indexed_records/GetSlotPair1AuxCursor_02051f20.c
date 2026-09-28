#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    void *slotPair1;
    int *slotPair1Aux;
} RecordManager;

extern RecordManager *g_recordManager_020613d0;

/* Reads the slot-pair-1 aux cursor. */
int GetSlotPair1AuxCursor_02051f20(int *out)
{
    RecordManager *manager = g_recordManager_020613d0;

    if (manager == 0 || manager->slotPair1 == 0) {
        return 0;
    }
    if (out != 0) {
        *out = *manager->slotPair1Aux - 4;
    }
    return (int)manager->slotPair1Aux + 4;
}
