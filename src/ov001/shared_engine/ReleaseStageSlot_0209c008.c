#include "nitro/types.h"

typedef struct StageSlots {
    u8 pad_00000[0x18d78];
    void *slots[1];
} StageSlots;

extern StageSlots *data_ov001_020a0508;
extern int func_ov001_0208f0bc(void *slot);

int ReleaseStageSlot_0209c008(int index)
{
    return func_ov001_0208f0bc(data_ov001_020a0508->slots[index]);
}
