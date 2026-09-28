#include "nitro/types.h"

typedef struct {
    u32 state[5];
    u8 buffer[0x40];
    u32 blockCount;
    u32 highBlockCount;
    u32 unused;
} HashContext;

/* SHA-1-style hash context reset */
void HashContextReset_0200d6d0(HashContext *ctx)
{
    ctx->highBlockCount = 0;
    ctx->unused = 0;
    ctx->blockCount = 0;
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xefcdab89;
    ctx->state[2] = 0x98badcfe;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xc3d2e1f0;
}
