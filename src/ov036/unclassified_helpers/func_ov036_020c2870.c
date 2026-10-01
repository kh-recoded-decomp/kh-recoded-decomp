#include "nitro/types.h"

extern u32 func_ov036_020c27ec(void *entry);

#define g_overlayWork (*(u8 **)0x020c3844)

u32 func_ov036_020c2870(void) {
    return func_ov036_020c27ec(g_overlayWork + 0x64fc);
}
