#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int (*callback)(int);
} CallbackHolder_0205fe00;

extern CallbackHolder_0205fe00 g_callbackHolder_0205fe00;

int func_020271e8(int value)
{
    return g_callbackHolder_0205fe00.callback(value);
}
