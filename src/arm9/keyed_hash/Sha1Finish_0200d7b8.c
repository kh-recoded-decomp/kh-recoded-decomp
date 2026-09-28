#include "nitro/types.h"

typedef struct {
    u32 state[5];
    u8 block[0x40];
    u32 pool;
    u32 blocksLow;
    u32 blocksHigh;
} Sha1Context;

extern void CopyBufferInChunks_0200d724(Sha1Context *ctx, const void *src, u32 size);
extern void FillBufferInChunks_0200d604(Sha1Context *ctx, int value, u32 size);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern const u8 data_02052ae0[];
extern const u8 data_02052ae1[];

#define BSWAP32(x) ((((x) >> 24) & 0xff) | (((x) >> 8) & 0xff00) | (((x) << 8) & 0xff0000) | (((x) << 24) & 0xff000000))

void Sha1Finish_0200d7b8(Sha1Context *ctx, void *digest)
{
    u32 footer[2];
    u32 bits;

    bits = (ctx->blocksLow << 9) + (ctx->pool << 3);
    footer[1] = BSWAP32(bits);
    bits = (ctx->blocksHigh << 9) + (ctx->blocksLow >> 23);
    footer[0] = BSWAP32(bits);

    CopyBufferInChunks_0200d724(ctx, data_02052ae0, 1);
    if (0x40 - ctx->pool < 8) {
        CopyBufferInChunks_0200d724(ctx, data_02052ae1, 0x40 - ctx->pool);
    }
    FillBufferInChunks_0200d604(ctx, 0, 0x38 - ctx->pool);
    CopyBufferInChunks_0200d724(ctx, footer, 8);

    ctx->state[0] = BSWAP32(ctx->state[0]);
    ctx->state[1] = BSWAP32(ctx->state[1]);
    ctx->state[2] = BSWAP32(ctx->state[2]);
    ctx->state[3] = BSWAP32(ctx->state[3]);
    ctx->state[4] = BSWAP32(ctx->state[4]);
    MI_CpuCopy8_01ff89a8(ctx, digest, 0x14);
}
