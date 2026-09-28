#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;

void func_ov035_020bb2d4(int enable) {
    if (enable != 0) {
        *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) | 4;
        return;
    }
    *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) & 0xfffb;
}
