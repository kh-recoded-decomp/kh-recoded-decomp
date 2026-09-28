#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    u32 *block;
} Container;

extern BOOL func_0200d290(void *ctx);

void func_0200cd34(Container *container)
{
    u32 *block = container->block;

    func_0200d290(container);
    block[0] = 0;
    block[1] = 0;
    block[2] = 0;
    block[3] = 0;
    block[4] = 0;
    block[5] = 0;
    block[6] = 0;
}
