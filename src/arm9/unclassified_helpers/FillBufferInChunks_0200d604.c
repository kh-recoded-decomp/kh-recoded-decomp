#include "nitro/types.h"

extern void func_01ff8830(void *dst, int value, int size);
extern void (*data_02055c40)(void *ctx);

typedef struct {
    u8 pad_00[0x14];
    u8 buffer[0x40];
    u32 position;
    u32 blockCountLow;
    u32 blockCountHigh;
} FillContext;

void FillBufferInChunks_0200d604(FillContext *ctx, int value, u32 size)
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
        func_01ff8830(ctx->buffer + ctx->position, value, chunk);
        size -= chunk;
        ctx->position += chunk;
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
