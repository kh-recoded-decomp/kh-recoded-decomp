#include "nitro/types.h"

extern u32 data_ov001_020a04ec;
extern void ReleaseResourceAndDetach(void *ptr);

void func_ov001_0207d680(void)
{
    u8 *context;

    context = (u8 *)data_ov001_020a04ec;
    if ((*(u16 *)(data_ov001_020a04ec + 0x108) & 2) != 0) {
        ReleaseResourceAndDetach(context + 0x1b8);
        ReleaseResourceAndDetach(context + 700);
    }
    if ((*(u16 *)(context + 0x108) & 4) != 0) {
        ReleaseResourceAndDetach(context + 0x3d8);
        ReleaseResourceAndDetach(context + 0x4dc);
    }
    if ((*(u16 *)(context + 0x108) & 0x10) != 0) {
        ReleaseResourceAndDetach(context + 0x600);
    }
    if ((*(u16 *)(context + 0x108) & 0x80) != 0) {
        ReleaseResourceAndDetach(context + 0x808);
        ReleaseResourceAndDetach(context + 0x704);
    }
    *(u32 *)(context + 0xf0) = 0;
    *(u32 *)(context + 0xf8) = 0;
    *(u16 *)(context + 0x108) = 0;
}
