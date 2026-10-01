#include "nitro/types.h"

typedef struct StageSlots {
    u8 pad_00000[0x18d78];
    void *slots[1];
} StageSlots;

extern StageSlots *data_ov001_020a0508;
extern int func_ov001_0208f1a8(void *slot, int entry);

int ReleaseStageSlotEntry_0209c024(int index, int slot)
{
    return func_ov001_0208f1a8(data_ov001_020a0508->slots[index], slot);
}
