#include "nitro/types.h"

extern u32 func_0200cd18(u32 target, u32 context, u32 output);
extern void *data_020529e0;

typedef struct {
    u8 pad_00[0x24];
    void *vtable;
} TypedNode;

typedef struct {
    u8 pad_00[8];
    TypedNode *target;
} SpanContext;

u32 CheckTypeAndComputeSpan_0200d05c(SpanContext *context, u32 output)
{
    // Verifies node type before computing span
    u32 matched = 0;
    TypedNode *target = context->target;
    if (target->vtable == &data_020529e0 &&
        func_0200cd18((u32)target, (u32)context, output) == 0) {
        matched = 1;
    }
    return matched;
}
