#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc0];
    u32 flags;
} FieldUnit;

extern BOOL StepFieldObjectAnim_020a2b1c(FieldUnit *unit);
extern void func_ov016_020a2c44(FieldUnit *unit);
extern void EnterFieldUnitPhase6_020a29a4(FieldUnit *unit);

BOOL UpdateFieldUnitAnimPhase_020a57e8(FieldUnit *unit)
{
    if ((unit->flags & 0x40) && StepFieldObjectAnim_020a2b1c(unit)) {
        unit->flags &= ~0x40;
    }
    func_ov016_020a2c44(unit);
    if (!(unit->flags & 0x60)) {
        EnterFieldUnitPhase6_020a29a4(unit);
    }
    return FALSE;
}
