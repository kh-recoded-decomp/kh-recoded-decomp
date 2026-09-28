#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern u32 data_ov040_020be260;
extern int func_ov001_0206a814();
extern int func_ov001_0207b36c();

u32 func_ov040_020bd628(void)
{
    int ready;

    ready = func_ov001_0206a814();
    if (ready == 0) {
        return 0xffffffff;
    }
    if (((*(u16 *)(data_ov035_020bc4e0 + 6) & 0x10) == 0) &&
        (ready = func_ov001_0207b36c(), ready == 0)) {
        return 0xffffffff;
    }
    *(u32 *)(data_ov040_020be260 + 0x144) = 2;
    return 0x11;
}
