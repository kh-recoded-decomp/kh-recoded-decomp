#include "nitro/types.h"

typedef struct {
    u8 opaque[0x60];
} HashContext;

extern void HashContextReset_0200d6d0(HashContext *ctx);
extern void func_0200d724(HashContext *ctx, const void *data, u32 len);
extern void func_0200d7b8(HashContext *ctx, void *digest);

/* one-shot SHA-1-style digest of a buffer */
void ComputeHash_0200d9b0(void *digest, const void *data, u32 len, u32 unused)
{
    HashContext ctx;

    HashContextReset_0200d6d0(&ctx);
    func_0200d724(&ctx, data, len);
    func_0200d7b8(&ctx, digest);
}
