#include "nitro/types.h"

extern u32 func_ov001_0206881c(void);
extern s32 func_ov001_02063a38(void);
extern void func_ov035_020bb378(u32 param);
extern void func_ov001_0208772c(u16 param);
extern void func_ov001_020876fc(u16 param);

void func_ov001_020688d4(u32 value, s32 hasValue, s32 flag)
{
    s32 mode;

    if (hasValue == 0) {
        value = func_ov001_0206881c();
    }
    mode = func_ov001_02063a38();
    if (mode == 6) {
        func_ov035_020bb378(value);
    }
    if (flag != 0) {
        func_ov001_0208772c(value & 0xffff);
        return;
    }
    func_ov001_020876fc(value & 0xffff);
}
