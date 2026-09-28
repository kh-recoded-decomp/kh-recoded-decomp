#include "nitro/types.h"

extern u32 func_02029370();
extern u32 PXI_Init_02064a30();

void func_ov001_02064aa8(u16 *value) {
    s32 result = PXI_Init_02064a30(*value);
    if (result != 0) {
        func_02029370(*value);
    }
}
