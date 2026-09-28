#include "nitro/types.h"

extern u32 func_02036a90(u32 argument0, u32 argument1);
extern u8 *g_recordTablePtr_0206083c;

void func_02036a70(int index, u32 value) {
    void **slots = (void **)(g_recordTablePtr_0206083c + 0x20);
    func_02036a90((u32)slots[index], value);
}
