#include "nitro/types.h"

extern u32 data_ov001_020a04d8;
extern void func_ov001_0207eef4(void);
extern void func_0202eee8();
extern void func_0202a1c4(void *ptr);
extern void func_ov001_020870cc(void);

void func_ov001_0207ef78(void)
{
    u8 *context;

    context = (u8 *)data_ov001_020a04d8;
    func_ov001_0207eef4();
    *(u32 *)(context + 0x120) = 0;
    if (*(s32 *)(context + 0x11c) != 0) {
        func_0202eee8();
        func_0202a1c4(*(void **)(context + 0x11c));
        *(u32 *)(context + 0x11c) = 0;
    }
    func_ov001_020870cc();
}
