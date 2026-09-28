#include "nitro/types.h"

typedef unsigned int UNDEF4;

typedef struct Actor {
    u8 pad_000[0x894];
    u8 animState[1];
} Actor;

extern void func_ov001_02089118(void *request, void *animState);
extern void func_ov001_02089180(Actor *actor);

void func_ov001_02089374(Actor *actor, UNDEF4 param2, UNDEF4 param3, UNDEF4 param4)
{
    u8 stackBuffer[0xc];
    UNDEF4 stackValue;

    stackValue = param4;
    func_ov001_02089118(stackBuffer, actor->animState);
    func_ov001_02089180(actor);
}
