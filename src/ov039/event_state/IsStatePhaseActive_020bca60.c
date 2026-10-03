#include "nitro/types.h"

extern int data_ov039_020bea00;

BOOL IsStatePhaseActive_020bca60(void)
{
    int base = data_ov039_020bea00;
    int phase;
    BOOL active;

    if (base == 0) {
        return FALSE;
    }
    phase = *(int *)(base + 0xc9c4);
    active = TRUE;
    if (phase != 1 && phase != 2) {
        active = FALSE;
    }
    return active ? TRUE : FALSE;
}
