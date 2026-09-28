#include "nitro/types.h"

extern u32 g_reentryGuard_02056014;

extern void func_0202d314(void *archive, int extra);
extern void func_0202d098(void *archive, int extra);
extern void func_0202e854(void *param1, void *param2, void *archive, void *param4);

/* Guarded resource dispatch that clears one slot field. */
int DispatchResourceLoad_0202ea78(void *param1, void *param2, int *archive, void *param4)
{
    u32 savedGuard = g_reentryGuard_02056014;
    g_reentryGuard_02056014 = 1;
    if (*archive == 0x4850414b) {
        func_0202d314(archive, 1);
    } else {
        func_0202d098(archive, 0);
    }
    g_reentryGuard_02056014 = savedGuard;
    func_0202e854(param1, param2, archive, param4);
    *(u32 *)((u8 *)param1 + 0xc) = 0;
    return 1;
}
