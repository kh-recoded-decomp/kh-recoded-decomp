#include "nitro/types.h"

typedef struct {
    u32 digestSize;
    u32 blockSize;
    void *self;
    void *digestBuf;
    void (*reset)(void *self);
    void (*update)(void *self, const void *data, u32 len);
    void (*finish)(void *self, void *out);
} HashOps;

typedef struct {
    u32 state[5];
    u8 buffer[0x40];
    u32 blockCount;
    u32 highBlockCount;
    u32 unused;
} HashContext;

extern const HashOps data_02052aec;
extern void HashContextReset_0200d6d0(void *ctx);
extern void CopyBufferInChunks_0200d724(void *ctx, const void *data, u32 len);
extern void func_0200d7b8(void *ctx, void *out);
extern void ComputeKeyedHash_0200da88(void *out, const void *msg, u32 msgLen, const void *key,
                                       u32 keyLen, HashOps *ops);

void ComputeHMACSHA1_0200d9f4(void *out, const void *msg, u32 msgLen, const void *key, u32 keyLen)
{
    HashContext context;
    u8 digest[20];
    HashOps ops = data_02052aec;

    ops.self = &context;
    ops.digestBuf = digest;
    ops.reset = HashContextReset_0200d6d0;
    ops.update = CopyBufferInChunks_0200d724;
    ops.finish = func_0200d7b8;
    ComputeKeyedHash_0200da88(out, msg, msgLen, key, keyLen, &ops);
}
