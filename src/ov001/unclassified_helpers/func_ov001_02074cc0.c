#include "nitro/types.h"

extern u32 data_ov001_020a04ac;
extern void func_0202a1c4();

void func_ov001_02074cc0(void)
{
    u32 context;
    s32 index;

    context = data_ov001_020a04ac;
    if (*(s32 *)(context + 0x18) != 0) {
        func_0202a1c4();
    }
    if (*(s32 *)(context + 0x1c) != 0) {
        func_0202a1c4();
    }
    if (*(s32 *)(context + 0x20) != 0) {
        func_0202a1c4();
    }
    index = 0;
    do {
        if (*(s32 *)(context + index * 4) != 0) {
            func_0202a1c4();
        }
        if (*(s32 *)(context + index * 4 + 0xc) != 0) {
            func_0202a1c4();
        }
        index = index + 1;
    } while (index < 3);
    *(u32 *)(context + 0x28) = 0;
    data_ov001_020a04ac = 0;
}
