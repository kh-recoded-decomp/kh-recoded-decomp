#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1b0];
    u8 active;
} UnitState;

extern void ResetCountsAndSlots_020aeb6c(UnitState *unit);

void ResetUnitCounts_020bcf34(UnitState *unit) {
    unit->active = 0;
    ResetCountsAndSlots_020aeb6c(unit);
}
