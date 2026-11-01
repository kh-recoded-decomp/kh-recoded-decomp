#include "nitro/types.h"

extern BOOL func_02035930(void *entry, int a1, int a2, int a3);
extern u8 *g_recordTablePtr_0206083c;

BOOL func_020358b0(int index, int a1, int a2, int a3) {
    void **slots = (void **)(g_recordTablePtr_0206083c + 0x20);
    return func_02035930(slots[index], a1, a2, a3);
}
