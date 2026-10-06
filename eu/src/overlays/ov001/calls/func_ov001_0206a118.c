#include "nitro/types.h"

extern int func_ov001_0206a918(int obj);
extern int ZeroHalfThenFree(void *arg0);

extern u32 data_ov001_020a04a0;

void func_ov001_0206a118(void)
{
    func_ov001_0206a918(data_ov001_020a04a0 + 0x30);
    ZeroHalfThenFree(*(void **)(data_ov001_020a04a0 + 0x60));
    data_ov001_020a04a0 = 0;
}
