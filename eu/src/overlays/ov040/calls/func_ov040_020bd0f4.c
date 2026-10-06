#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern int func_ov001_0207b6b0();
extern void StoreToGlobalPtr4Field28();

u32 func_ov040_020bd0f4(void)
{
    int ready;

    ready = func_ov001_0207b6b0();
    if (ready == 0) {
        return 0xffffffff;
    }
    if ((*(u16 *)(data_ov035_020bc4e0 + 6) & 1) != 0) {
        *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) & 0xfffe;
    }
    StoreToGlobalPtr4Field28(0);
    return 5;
}
