#include "nitro/types.h"

extern u32 data_ov001_020a046c;
extern void func_ov001_020676c4(void);
extern void func_0202cd78(void *block);
extern void func_ov001_02067aa8(void);
extern void func_0202a1c4(void *block);

void func_ov001_0206747c(void)
{
    u8 *ctx;

    ctx = (u8 *)data_ov001_020a046c;
    func_ov001_020676c4();
    func_0202cd78(*(void **)(ctx + 4));
    func_ov001_02067aa8();
    func_0202a1c4((void *)data_ov001_020a046c);
    data_ov001_020a046c = 0;
}
