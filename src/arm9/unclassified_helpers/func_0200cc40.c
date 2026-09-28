#include "nitro/types.h"

extern u32 func_0200c9d4(u32 ctx, u32 start, u32 end, u32 *out, u32 flag);
extern void func_0200caa4(u32 ctx, u32 fallback, u32 value, u32 extra);

void func_0200cc40(u32 ctx, u32 fallback, u32 start, u32 end, u32 extra)
{
    u32 value;

    if (func_0200c9d4(ctx, start, end, &value, 0) == 0) {
        func_0200caa4(ctx, fallback, value, extra);
    }
}
