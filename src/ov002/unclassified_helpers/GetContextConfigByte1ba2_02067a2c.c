#include "nitro/types.h"

extern u32 func_ov002_02066fe0(void);

u8 GetContextConfigByte1ba2_02067a2c(void) {
    u32 base = func_ov002_02066fe0();
    return *(u8 *)(base + 0x1ba2);
}
