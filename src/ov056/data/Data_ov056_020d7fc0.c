#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ResetActiveEntries_020af20c(void);
extern void ResetCountsAndSlots_020aeb6c(void);
extern void ResetSlotStateAndNotify_020d6ac8(void);
extern void ResetUnitCounts_020bcf34(void);
extern void StopSlotsAndClearActive_020d7c38(void);

void *data_ov056_020d7fc0[20] = {
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetActiveEntries_020af20c,
    (void *)ResetCountsAndSlots_020aeb6c,
    NULL,
    NULL,
    NULL,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetActiveEntries_020af20c,
    (void *)ResetSlotStateAndNotify_020d6ac8,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)ResetCountsAndSlots_020aeb6c,
    (void *)StopSlotsAndClearActive_020d7c38,
    (void *)ResetUnitCounts_020bcf34,
};
