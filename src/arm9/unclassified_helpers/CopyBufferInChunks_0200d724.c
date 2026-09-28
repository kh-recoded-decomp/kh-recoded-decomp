#include "nitro/types.h"

extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern void (*data_02055c40)(void *ctx);

typedef struct {
    u8 pad_00[0x14];
    u8 buffer[0x40];
    u32 position;
    u32 blockCountLow;
    u32 blockCountHigh;
} FillContext;

void CopyBufferInChunks_0200d724(FillContext *ctx, const u8 *src, u32 size)
{
    u32 chunk;
    if (size == 0) {
        return;
    }
    do {
        chunk = 0x40 - ctx->position;
        if (chunk > size) {
            chunk = size;
        }
        MI_CpuCopy8_01ff89a8(src, ctx->buffer + ctx->position, chunk);
        src += chunk;
        ctx->position += chunk;
        size -= chunk;
        if (ctx->position >= 0x40) {
            data_02055c40(ctx);
            ctx->position = 0;
            ctx->blockCountLow++;
            if (ctx->blockCountLow == 0) {
                ctx->blockCountHigh++;
            }
        }
    } while (size != 0);
}
