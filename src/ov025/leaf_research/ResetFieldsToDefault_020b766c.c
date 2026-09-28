#include "nitro/types.h"

void ResetFieldsToDefault_020b766c(u32 entity) {
    *(u32 *)(entity + 0x98) = 0xffffff00;
    *(u32 *)(entity + 0x9c) = 1;
}
