#include "nitro/types.h"

extern int data_ov039_020bea00;

BOOL IsStatePhase4_020bca30(void)
{
    int base = data_ov039_020bea00;

    if (base == 0) {
        return 0;
    }
    return *(int *)(base + 0xc9c4) == 4;
}
