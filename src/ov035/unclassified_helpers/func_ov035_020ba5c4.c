#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern int func_ov001_0207ed2c(void);
extern void func_ov001_02087178(void);

u32 func_ov035_020ba5c4(void) {
    if (func_ov001_0207ed2c() == 0) {
        return 0xffffffff;
    }
    func_ov001_02087178();
    *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) | 0x8000;
    return 3;
}
