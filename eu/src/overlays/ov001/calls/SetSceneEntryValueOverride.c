#include "nitro/types.h"

extern u32 gFieldSceneEntryContext;

void SetSceneEntryValueOverride(u8 byteValue, u32 wordValue)
{
    u8 *ctx;

    ctx = (u8 *)gFieldSceneEntryContext;
    ctx[0x10c0] = byteValue;
    *(u32 *)(ctx + 0x10c4) = wordValue;
}
