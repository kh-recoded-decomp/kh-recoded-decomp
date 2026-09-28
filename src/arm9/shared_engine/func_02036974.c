#include "nitro/types.h"

extern void func_02036994(void *entry);
extern u8 *g_recordTablePtr_0206083c;

void func_02036974(int index) {
    void **slots = (void **)(g_recordTablePtr_0206083c + 0x20);
    func_02036994(slots[index]);
}
