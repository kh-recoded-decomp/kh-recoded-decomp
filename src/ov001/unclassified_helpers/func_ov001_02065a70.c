#include "nitro/types.h"

extern u32 func_ov001_0206cb20();
extern u32 func_ov001_0206e444();

u32 func_ov001_02065a70(s32 entry) {
    s32 result = func_ov001_0206cb20();
    if (result != 0) {
        return 1;
    }
    *(u32 *)(*(s32 *)(entry + 0x1c8) + 0x1c8) = 0;
    func_ov001_0206e444(1);
    return 0;
}
