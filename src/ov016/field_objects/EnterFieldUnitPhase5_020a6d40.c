#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0xbe - 0x44];
    u8 lowBits : 4;
    u8 phase : 4;
    u8 pad_bf;
    u32 flags;
} FieldUnit;

extern void func_ov016_020a2b08(FieldUnit *unit);
extern void func_ov016_020a2c0c(FieldUnit *unit);
extern void func_ov016_020a296c(FieldUnit *unit, BOOL doReset);
extern void SpawnSoundSlot_0204da8c(int bank, int id, VecFx32 *position, int flags);

void EnterFieldUnitPhase5_020a6d40(FieldUnit *unit, BOOL doReset)
{
    unit->phase = 5;
    func_ov016_020a2b08(unit);
    unit->flags |= 0x40;
    func_ov016_020a2c0c(unit);
    func_ov016_020a296c(unit, doReset);
    SpawnSoundSlot_0204da8c(0, 0x2d, &unit->position, 0);
}
