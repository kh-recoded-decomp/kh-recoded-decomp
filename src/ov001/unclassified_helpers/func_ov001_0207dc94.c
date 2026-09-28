#include "nitro/types.h"

extern u32 data_ov001_020a04d0;
extern void func_0202a1c4(void *ptr);

void func_ov001_0207dc94(void)
{
    u8 *context;

    context = (u8 *)data_ov001_020a04d0;
    func_0202a1c4(*(void **)(data_ov001_020a04d0 + 0x30));
    func_0202a1c4(*(void **)(context + 0x34));
    func_0202a1c4(*(void **)(context + 0x38));
    data_ov001_020a04d0 = 0;
}
