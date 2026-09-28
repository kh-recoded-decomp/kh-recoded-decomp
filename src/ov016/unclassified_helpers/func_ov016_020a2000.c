#include "nitro/types.h"

extern u32 func_ov016_020a1e64();
extern u32 func_ov001_02087214();
extern void func_ov016_020a6338();

u32 func_ov016_020a2000(u32 messageId, u32 arg1)
{
    u32 context;
    u32 cursor;
    u8 buffer[92];

    cursor = arg1;
    func_ov016_020a1e64(buffer, messageId, &cursor);
    context = func_ov001_02087214();
    func_ov016_020a6338(context, buffer);
    return 1;
}
