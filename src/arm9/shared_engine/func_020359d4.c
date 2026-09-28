#include "nitro/types.h"

extern int func_020359ec(int context);
extern u8 *g_recordTablePtr_0206083c;

int func_020359d4(int index) {
    void **slots = (void **)(g_recordTablePtr_0206083c + 0x20);
    return func_020359ec((int)slots[index]);
}
