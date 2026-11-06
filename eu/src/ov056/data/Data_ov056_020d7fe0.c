#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ResetActiveEntries(void);
extern void ResetCountsAndSlots(void);
extern void ResetSlotStateAndNotify(void);
extern void ResetUnitCounts(void);
extern void StopSlotsAndClearActive(void);

void *gEffectSourceKindResetHandlers[20] = {
    (void *)ResetCountsAndSlots,
    (void *)ResetCountsAndSlots,
    (void *)ResetCountsAndSlots,
    (void *)ResetCountsAndSlots,
    (void *)ResetActiveEntries,
    (void *)ResetCountsAndSlots,
    NULL,
    NULL,
    NULL,
    (void *)ResetCountsAndSlots,
    (void *)ResetCountsAndSlots,
    (void *)ResetCountsAndSlots,
    (void *)ResetCountsAndSlots,
    (void *)ResetActiveEntries,
    (void *)ResetSlotStateAndNotify,
    (void *)ResetCountsAndSlots,
    (void *)ResetCountsAndSlots,
    (void *)ResetCountsAndSlots,
    (void *)StopSlotsAndClearActive,
    (void *)ResetUnitCounts,
};
