#include "nitro/types.h"

extern u32 data_ov001_020a04fc;

int GetModeEntryUnlockRewardId(int index) {
    if (index < *(int *)(data_ov001_020a04fc + 0x1b8)) {
        return *(int *)(data_ov001_020a04fc + 0x1bc) + index * 2;
    }
    return 0;
}
