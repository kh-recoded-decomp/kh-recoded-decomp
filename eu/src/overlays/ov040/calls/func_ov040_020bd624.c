#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern int IsScreenModeIdle();
extern void BeginScreenFadeOut();

u32 func_ov040_020bd624(void)
{
    int ready;

    ready = IsScreenModeIdle();
    if (ready == 0) {
        return 0xffffffff;
    }
    BeginScreenFadeOut((int)*(s8 *)(data_ov035_020bc4e0 + 0x1c));
    return 0x10;
}
