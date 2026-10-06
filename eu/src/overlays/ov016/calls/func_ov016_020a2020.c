#include "nitro/types.h"

extern u32 func_ov016_020a1e84();
extern u32 func_ov001_0208723c();
extern void func_ov016_020a6358();

u32 func_ov016_020a2020(u32 messageId, u32 arg1)
{
    u32 context;
    u32 cursor;
    u8 buffer[92];

    cursor = arg1;
    func_ov016_020a1e84(buffer, messageId, &cursor);
    context = func_ov001_0208723c();
    func_ov016_020a6358(context, buffer);
    return 1;
}
