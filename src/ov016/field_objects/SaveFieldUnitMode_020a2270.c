#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x76];
    s8 mode;
    u8 pad_77[0xbf - 0x77];
    s8 savedMode;
} FieldUnit;

void SaveFieldUnitMode_020a2270(FieldUnit *unit)
{
    unit->savedMode = unit->mode;
}
