#include "nitro/types.h"

extern u32 data_ov001_020a0470;
extern void func_ov001_020685d4(void);
extern void func_02051dfc(s32 mode);
extern void func_ov001_02087678(void);
extern void func_0202a1c4(void *block);

void func_ov001_020685a4(void)
{
    u32 *ctx;

    ctx = (u32 *)data_ov001_020a0470;
    func_ov001_020685d4();
    func_02051dfc(4);
    func_ov001_02087678();
    if (*ctx != 0) {
        func_0202a1c4((void *)*ctx);
    }
    func_0202a1c4((void *)data_ov001_020a0470);
    data_ov001_020a0470 = 0;
}
