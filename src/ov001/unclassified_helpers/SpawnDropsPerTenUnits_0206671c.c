#include "nitro/types.h"

extern s32 func_02023dbc(s32 dividend, s32 divisor);
extern u32 func_ov001_020664f0(u32 kind, u32 isKind4, u32 position, u32 mode);

void SpawnDropsPerTenUnits_0206671c(s32 amount, u32 position, u32 kind) {
    s32 i;
    s32 count;
    BOOL isKind4 = (kind == 4);

    i = 0;
    count = func_02023dbc(amount, 10);
    for (; i < count; i++) {
        func_ov001_020664f0(kind, isKind4, position, 6);
    }
}
