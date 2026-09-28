#include "nitro/types.h"

typedef struct {
    u32 (*handler)(void);
    u8 pad_04[0x14];
} HandlerEntry;

extern HandlerEntry data_0205576c[];

/* Calls a handler by index if present. */
u32 CallIndexedHandler_0202b3b8(s32 index)
{
    u32 (*handler)(void) = data_0205576c[index].handler;

    if (handler != NULL) {
        return handler();
    }
    return 0;
}
