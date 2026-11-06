#include "nitro/types.h"

extern u32 gFieldEffectPool;

u32 HasActiveFieldEffects(void) {
    if (*(s32 *)(gFieldEffectPool + 0x4c) != 0) {
        return 1;
    }
    return 0;
}
