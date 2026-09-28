#include "nitro/types.h"

extern u32 func_ov001_020667b4();
extern u32 func_ov001_02066810();
extern u32 func_ov001_0206685c();
extern u32 func_ov001_02066874();

u32 func_ov001_02065b8c(void) {
    s32 result;

    func_ov001_02066874(0);
    result = func_ov001_0206685c();
    if (result != 0) {
        return 0;
    }
    func_ov001_02066810();
    func_ov001_020667b4();
    return 1;
}
