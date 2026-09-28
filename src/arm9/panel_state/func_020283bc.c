#include "nitro/types.h"

extern void *g_ptr_0205fe24;
extern void func_0202849c(void *state, int page, int delta);

void func_020283bc(int slot)
{
    u8 *base = (u8 *)g_ptr_0205fe24;
    int byteOffset = slot * 8;
    u8 *timerBase = base + 0x74;
    s32 timer = *(s32 *)(timerBase + byteOffset) + 1;
    *(s32 *)(timerBase + byteOffset) = timer;
    if (timer >= 0x10) {
        s32 mode = (*(s32 *)(base + byteOffset + 0x78) == 1) ? 2 : 1;
        *(s32 *)(base + 0x78 + byteOffset) = mode;
        *(s32 *)(timerBase + byteOffset) = 0;
        func_0202849c(base + 0xc, slot, *(s32 *)(base + 0x78 + byteOffset));
    }
}
