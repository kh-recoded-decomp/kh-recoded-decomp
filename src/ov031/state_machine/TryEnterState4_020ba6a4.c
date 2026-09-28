#include "nitro/types.h"

extern u32 func_ov001_02067704(void);
extern u32 func_ov001_02086d00(void);

u32 TryEnterState4_020ba6a4(void)
{
    u32 result;

    result = func_ov001_02086d00();
    if (result == 0) {
        return 0xffffffff;
    }
    func_ov001_02067704();
    return 4;
}
