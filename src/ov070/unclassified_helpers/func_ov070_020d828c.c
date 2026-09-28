#include "nitro/types.h"

extern int ZeroHalfThenFree_0202cd78(void *arg0);

typedef struct {
    u8 pad_00[0x1C8];
    void *buffer;
} UnkContext_020d828c;

void func_ov070_020d828c(UnkContext_020d828c *ctx) {
    ZeroHalfThenFree_0202cd78(ctx->buffer);
}
