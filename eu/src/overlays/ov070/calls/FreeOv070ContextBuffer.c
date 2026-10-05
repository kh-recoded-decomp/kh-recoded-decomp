#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c8];
    void *buffer;
} Ov070Context;

extern int ZeroHalfThenFree(void *buffer);

void FreeOv070ContextBuffer(Ov070Context *ctx)
{
    ZeroHalfThenFree(ctx->buffer);
}
