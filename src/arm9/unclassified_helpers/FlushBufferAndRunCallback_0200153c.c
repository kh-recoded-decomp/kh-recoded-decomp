#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    void *bufferAddr;
} InnerBlock;

typedef struct {
    u8 pad_00[0x20];
    InnerBlock *block;
    u8 pad_24[4];
    u32 size;
    u16 multiplier1;
    u8 pad_2e[0x32 - 0x2e];
    u8 multiplier2;
    u8 tableIndex;
} Context_0200153c;

extern void func_0200344c(void *dst, u32 size);
extern void func_020033e0(void);
extern void Callbacks_RunTableEntry_0202b3d4(int index, int arg1, int arg2, int arg3);

void FlushBufferAndRunCallback_0200153c(Context_0200153c *context)
{
    void *bufferAddr = context->block->bufferAddr;

    if (context->size >= 0x2400) {
        func_020033e0();
    } else {
        func_0200344c(bufferAddr, context->size);
    }
    Callbacks_RunTableEntry_0202b3d4(context->tableIndex, (int)context->block->bufferAddr,
                                      context->multiplier2 * context->multiplier1,
                                      context->size);
}
