#include "nitro/types.h"

extern u32 IsGlobalPackedBitSet();
extern u32 FieldObject_SetEnabled();

void
DisableTargetViewForSavedFlag(int self)
{
    int result;

    if ((*(char *)(self + 0x59) == '\x01') &&
        (result = IsGlobalPackedBitSet(*(char *)(self + 0x5a) + 0x580), result != 0)) {
        FieldObject_SetEnabled(self, 0);
    }
}
