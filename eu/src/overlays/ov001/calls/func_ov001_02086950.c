#include "nitro/types.h"

extern u32 data_ov001_020a04fc;

int func_ov001_02086950(int index) {
    if (index < *(int *)(data_ov001_020a04fc + 0x1c0)) {
        return *(int *)(data_ov001_020a04fc + 0x1c4) + index * 6;
    }
    return 0;
}
