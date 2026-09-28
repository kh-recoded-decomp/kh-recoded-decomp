#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 baseAddr;
} SharedContext_0205fe00;

extern SharedContext_0205fe00 g_sharedContext_0205fe00;
extern void func_02051d3c(int a, int b);
extern void func_02051dfc(int a);
extern s32 func_020277f4(u32 handle, s32 *outIndex, u8 *outFlags);

s32 func_0202761c(u32 handle)
{
    s32 index;
    u8 flags[4];
    s32 result;
    u32 base;

    func_02051d3c(9, 1);
    result = func_020277f4(handle, &index, flags);
    func_02051dfc(9);

    base = g_sharedContext_0205fe00.baseAddr + 0x2788;
    if (result == 0) {
        *(u8 *)(base + index) |= flags[0];
        base += 0x67;
        *(u8 *)(base + index) |= flags[0];
    }
    return 1;
}
