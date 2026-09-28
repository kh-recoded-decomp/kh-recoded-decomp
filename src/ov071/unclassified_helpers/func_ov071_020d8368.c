#include "nitro/types.h"

/* Stores a value into an actor field. */
void func_ov071_020d8368(u32 self, int actor, u32 value)
{
    *(u32 *)(actor + 0x7c) = value;
}
