#define func_ov001_0206db78 GetPlayerControlState
#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0x930];
    u8 playerIndex;
} Actor;

extern void *func_ov001_0206db78(u32 playerIndex);

BOOL func_ov059_020c99ec(Actor *actor)
{
    func_ov001_0206db78(actor->playerIndex);
    return FALSE;
}
