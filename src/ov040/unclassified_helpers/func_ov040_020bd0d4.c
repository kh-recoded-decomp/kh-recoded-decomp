#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern int func_ov001_0207b688();
extern void func_0202a778();

u32 func_ov040_020bd0d4(void)
{
    int ready;

    ready = func_ov001_0207b688();
    if (ready == 0) {
        return 0xffffffff;
    }
    if ((*(u16 *)(data_ov035_020bc4e0 + 6) & 1) != 0) {
        *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) & 0xfffe;
    }
    func_0202a778(0);
    return 5;
}
