#include "nitro/types.h"

typedef void (*HandlerFunc)(void *target, u32 arg0, u32 arg1);

typedef struct {
    u8 pad_00[0x14];
    void *target;
} HandlerOwner;

extern HandlerFunc data_ov036_020c385c[];

void func_ov036_020bf670(int handlerIndex, HandlerOwner *owner, u32 arg0, u32 arg1) {
    data_ov036_020c385c[handlerIndex](owner->target, arg0, arg1);
}
