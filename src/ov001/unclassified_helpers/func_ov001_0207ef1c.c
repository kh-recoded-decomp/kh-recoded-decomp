#include "nitro/types.h"

extern u32 data_ov001_020a04d8;
extern void func_ov001_0207f694(void *node);
extern void func_ov001_02087010(void);

void func_ov001_0207ef1c(void)
{
    u8 *node;

    for (node = *(u8 **)(data_ov001_020a04d8 + 8); node != 0; node = *(u8 **)(node + 4)) {
        func_ov001_0207f694(node);
    }
    func_ov001_02087010();
}
