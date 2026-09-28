#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern s32 func_ov001_0206910c(u32 fieldAddr);
extern u32 func_ov001_02062c98();
extern u32 func_ov001_020630e4();

s32 func_ov001_0206257c(void) {
    u32 base = data_ov001_020a0460;
    s32 result = -1;
    s32 status = func_ov001_0206910c(data_ov001_020a0460 + 0x24);

    switch (status) {
    case 0:
        *(u8 *)(data_ov001_020a0460 + 0x1b) = 1;
        result = 8;
        break;
    case 1:
        func_ov001_02062c98(base, 1);
        func_ov001_020630e4();
        result = 4;
        break;
    }
    return result;
}
