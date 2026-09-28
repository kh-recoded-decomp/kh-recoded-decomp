#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 *data;
} MainDataHolder_0205fe00;

extern MainDataHolder_0205fe00 g_mainDataHolder_0205fe00;

u32 func_020273c0(void)
{
    return (*(u32 *)(g_mainDataHolder_0205fe00.data + 0x2780) << 19) >> 25;
}
