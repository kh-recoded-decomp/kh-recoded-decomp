#include "nitro/types.h"

extern void func_020358c8(void *entry, int a1, int a2, int a3);
extern u8 *g_recordTablePtr_0206083c;

void func_02035898(int index, int a1, int a2, int a3) {
    void **slots = (void **)(g_recordTablePtr_0206083c + 0x20);
    func_020358c8(slots[index], a1, a2, a3);
}
