#include "nitro/types.h"

typedef void (*HandlerFunc)(void *target, u32 arg0, u32 arg1);

typedef struct {
    u8 pad_00[0xC];
    u8 body[1];
} HandlerOwner;

extern HandlerFunc gTextSceneBgScreenLoaders[];

void func_ov036_020bf6b8(int handlerIndex, HandlerOwner *owner, u32 arg0, u32 arg1) {
    gTextSceneBgScreenLoaders[handlerIndex](owner->body, arg0, arg1);
}
