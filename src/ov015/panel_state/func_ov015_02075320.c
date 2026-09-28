#include "nitro/types.h"

extern u32 func_ov015_020763a8(void);
extern void func_ov015_020764c4(void);

u32 func_ov015_02075320(void) {
    u32 result;

    result = func_ov015_020763a8();
    func_ov015_020764c4();
    return result;
}
