#include "nitro/types.h"

extern u32 *func_ov008_020a125c(u32 *list, u32 index);

/* Marks an indexed slot as free. */
void ReleaseSlot_020a131c(u32 *list, u32 index)
{
    u32 *slot;

    slot = func_ov008_020a125c(list, index);
    if (slot != 0) {
        *slot = 0;
    }
}
