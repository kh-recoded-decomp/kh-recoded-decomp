#include "nitro/types.h"

extern u8 *func_ov001_0209c120(u16 index);
extern u16 func_ov001_0209c26c(u8 *actor);

void RegisterActorSlotInEntity_02097d64(u8 *actor)
{
    u8 *entity = func_ov001_0209c120(*(u16 *)(actor + 0x1d2));

    if (entity != 0) {
        *(u16 *)(entity + 0xc) = func_ov001_0209c26c(actor);
    }
}
