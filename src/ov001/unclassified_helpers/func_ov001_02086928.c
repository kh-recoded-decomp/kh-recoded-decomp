#include "nitro/types.h"

extern u32 data_ov001_020a04dc;

int func_ov001_02086928(int index) {
    if (index < *(int *)(data_ov001_020a04dc + 0x1c0)) {
        return *(int *)(data_ov001_020a04dc + 0x1c4) + index * 6;
    }
    return 0;
}
