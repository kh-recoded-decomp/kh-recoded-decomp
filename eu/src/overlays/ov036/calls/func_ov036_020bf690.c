#include "nitro/types.h"

typedef void (*HandlerFunc)(void *target, u32 arg0, u32 arg1);

typedef struct {
    u8 pad_00[0x14];
    void *target;
} HandlerOwner;

extern HandlerFunc gTextSceneBgCharacterLoaders[];

void func_ov036_020bf690(int handlerIndex, HandlerOwner *owner, u32 arg0, u32 arg1) {
    gTextSceneBgCharacterLoaders[handlerIndex](owner->target, arg0, arg1);
}
