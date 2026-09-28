#include "nitro/types.h"

extern void func_02035a18(void *entry, int param2, int param3);
extern u8 *g_recordTablePtr_0206083c;

void func_020359f8(int index, int param2, int param3) {
    void **slots = (void **)(g_recordTablePtr_0206083c + 0x20);
    func_02035a18(slots[index], param2, param3);
}
