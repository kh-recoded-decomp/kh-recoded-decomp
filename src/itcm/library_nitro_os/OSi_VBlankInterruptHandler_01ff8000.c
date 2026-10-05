#include "nitro/types.h"

typedef struct VBlankNode {
    u32 pad[5];
    void (*func)(void);
    struct VBlankNode *next;
} VBlankNode;

typedef struct VBlankCtx {
    u32 counter;
    s32 listIndex;
    u32 pad;
    VBlankNode *lists[1];
} VBlankCtx;

extern void func_02006748(u16 *dst, int value);

extern u8 data_02060388;
extern s8 data_02060389[];
extern VBlankCtx data_020569cc;
extern u32 data_020569c8;
extern char data_027e0000[];

void OSi_VBlankInterruptHandler_01ff8000(void) {
    VBlankCtx *ctx;
    VBlankNode *node;
    u8 flags;

    ctx = &data_020569cc;
    flags = data_02060388;
    ctx->counter++;
    if (flags & 1) {
        func_02006748((u16 *)0x0400006C, data_02060389[0]);
    }
    if (flags & 2) {
        func_02006748((u16 *)0x0400106C, data_02060389[1]);
    }
    data_02060388 = 0;
    data_020569c8 |= 1;
    node = ctx->lists[ctx->listIndex];
    while (node) {
        node->func();
        node = node->next;
    }
    data_020569c8 &= ~1;
    {
        u32 base = (u32)data_027e0000 + 0x3000;
        *(u32 *)(base + 0xFF8) |= 1;
    }
}
