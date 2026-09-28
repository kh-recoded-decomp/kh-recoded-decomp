#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern int func_ov001_0206a814();
extern void func_ov001_0206a7c0();

u32 func_ov040_020bd604(void)
{
    int ready;

    ready = func_ov001_0206a814();
    if (ready == 0) {
        return 0xffffffff;
    }
    func_ov001_0206a7c0((int)*(s8 *)(data_ov035_020bc4e0 + 0x1c));
    return 0x10;
}
