#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void *g_actorRegistry_0206083c;

BOOL func_0203574c(void) {
    if (g_actorRegistry_0206083c == NULL) {
        g_actorRegistry_0206083c = NNSi_FndAllocFromDefaultHeap_0202a178(0xc30);
    }
    func_01ff8830(g_actorRegistry_0206083c, 0, 0xc30);
    return TRUE;
}
