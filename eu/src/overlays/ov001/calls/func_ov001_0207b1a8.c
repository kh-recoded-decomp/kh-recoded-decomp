#include "nitro/types.h"
#include "src/overlays/ov001/FieldTextFormats.h"

extern u32 data_ov001_020a04e8;

u8 *func_ov001_0207b1a8(void)
{
    u8 *data;

    if ((data_ov001_020a04e8 == 0) ||
        (data = *(u8 **)(data_ov001_020a04e8 + 0x18), data == (u8 *)0x0)) {
        data = (u8 *)gFieldTextFormats.empty;
    }
    return data;
}
