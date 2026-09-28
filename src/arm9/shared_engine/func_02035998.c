#include "nitro/types.h"

extern void func_020359b0(void *entry);
extern u8 *g_recordTablePtr_0206083c;

void func_02035998(int index) {
    void **slots = (void **)(g_recordTablePtr_0206083c + 0x20);
    func_020359b0(slots[index]);
}
