#include "nitro/types.h"

extern u32 data_ov035_020bc500;

void func_ov035_020bb2f4(int enable) {
    if (enable != 0) {
        *(u16 *)(data_ov035_020bc500 + 6) = *(u16 *)(data_ov035_020bc500 + 6) | 4;
        return;
    }
    *(u16 *)(data_ov035_020bc500 + 6) = *(u16 *)(data_ov035_020bc500 + 6) & 0xfffb;
}
