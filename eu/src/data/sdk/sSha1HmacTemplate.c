#include "nitro/types.h"

typedef struct HmacHashOps {
    u32 digestSize;
    u32 blockSize;
    void *context;
    void *digestBuffer;
    void (*reset)(void *context);
    void (*update)(void *context, const void *data, u32 size);
    void (*finish)(void *context, void *digest);
} HmacHashOps;

typedef char HmacHashOpsMustBe28Bytes[sizeof(HmacHashOps) == 28 ? 1 : -1];

/* MATH_CalcHMACSHA1 supplies the per-call context, buffer and callbacks. */
const HmacHashOps sSha1HmacTemplate = { 20, 64, NULL, NULL, NULL, NULL, NULL };
