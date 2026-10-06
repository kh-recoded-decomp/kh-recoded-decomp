#include "nitro/types.h"

extern u32 FindFreeEffectSlot();
extern u32 SpawnEffect();

u32 func_ov001_020664f0(u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    s32 slot = FindFreeEffectSlot();
    if (slot < 0) {
        return 0;
    }
    return SpawnEffect(slot, arg1, arg2, arg3, arg4);
}
