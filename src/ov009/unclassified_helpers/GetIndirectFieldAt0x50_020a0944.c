#include "nitro/types.h"

u32 GetIndirectFieldAt0x50_020a0944(int obj) {
    return *(u32 *)(*(int *)(obj + 8) + 0x50);
}
