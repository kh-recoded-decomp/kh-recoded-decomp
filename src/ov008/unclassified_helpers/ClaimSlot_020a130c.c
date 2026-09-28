#include "nitro/types.h"

extern u32 *func_ov008_020a125c(u32 *list, u32 index);

/* Marks an indexed slot as in use. */
void ClaimSlot_020a130c(u32 *list, u32 index)
{
    u32 *slot;

    slot = func_ov008_020a125c(list, index);
    if (slot != 0) {
        *slot = 1;
    }
}
