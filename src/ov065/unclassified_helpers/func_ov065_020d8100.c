#include "nitro/types.h"

extern u32 func_ov001_0206db5c(u32 index);
extern void func_ov046_020c2f44(u32 panel);
extern void func_ov052_020d1170(u32 entry, u32 index);

/* Resets an entry and refreshes its panel. */
u32 func_ov065_020d8100(int context, int params, u32 *outStatus)
{
    u32 entry;

    entry = func_ov001_0206db5c(*(u32 *)(context + 0x14));
    *(u8 *)(entry + 0xa51) = 0;
    func_ov046_020c2f44(*(u32 *)(params + 0x9c));
    func_ov052_020d1170(entry, 0);
    *outStatus = 0x18;
    return *(u32 *)(params + 0x3c);
}
