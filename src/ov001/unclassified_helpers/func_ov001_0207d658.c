#include "nitro/types.h"

extern u32 data_ov001_020a04cc;
extern void func_0202eee8(void *ptr);

void func_ov001_0207d658(void)
{
    u8 *context;

    context = (u8 *)data_ov001_020a04cc;
    if ((*(u16 *)(data_ov001_020a04cc + 0x108) & 2) != 0) {
        func_0202eee8(context + 0x1b8);
        func_0202eee8(context + 700);
    }
    if ((*(u16 *)(context + 0x108) & 4) != 0) {
        func_0202eee8(context + 0x3d8);
        func_0202eee8(context + 0x4dc);
    }
    if ((*(u16 *)(context + 0x108) & 0x10) != 0) {
        func_0202eee8(context + 0x600);
    }
    if ((*(u16 *)(context + 0x108) & 0x80) != 0) {
        func_0202eee8(context + 0x808);
        func_0202eee8(context + 0x704);
    }
    *(u32 *)(context + 0xf0) = 0;
    *(u32 *)(context + 0xf8) = 0;
    *(u16 *)(context + 0x108) = 0;
}
