#include "nitro/types.h"

typedef struct RetryCounter {
    u8 pad_000[0x1c8];
    s32 count;
} RetryCounter;

typedef struct RetryContext {
    u8 pad_000[0x1c8];
    RetryCounter *counter;
} RetryContext;

extern void func_ov001_0206ca68(int a, int b, int c);

BOOL func_ov001_02065a94(RetryContext *context)
{
    func_ov001_0206ca68(0, 1, 0);
    context->counter->count++;
    if (context->counter->count >= 15) {
        context->counter->count = 0;
        return TRUE;
    }
    return FALSE;
}
