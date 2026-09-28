#include "nitro/types.h"

extern u8 *func_ov001_0209c0ec(u16 index);
extern u16 func_ov001_0209c26c(u8 *actor);

void RegisterActorSlotInRecord_02091cf8(u8 *actor)
{
    u8 *record = func_ov001_0209c0ec(*(u16 *)(actor + 0x1d2));

    if (record != 0) {
        *(u16 *)(record + 0x10) = func_ov001_0209c26c(actor);
    }
}
