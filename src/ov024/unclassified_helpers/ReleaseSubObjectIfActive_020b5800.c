#include "nitro/types.h"

extern u32 g_context_020b7520;
extern void func_ov027_020b8c94(u32 target, u32 mode);

void ReleaseSubObjectIfActive_020b5800(void) {
    if (*(int *)(g_context_020b7520 + 0x64f4) != 0) {
        func_ov027_020b8c94(g_context_020b7520 + 0x74, 0);
        *(u32 *)(g_context_020b7520 + 0x64f4) = 0;
    }
}
