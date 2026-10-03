#include "nitro/types.h"

typedef struct {
    u8 data[0x28];
} UnitRecord;

typedef struct {
    u8 pad_00[0xd0];
    UnitRecord *entries;
} FieldUnit;

extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);

void StoreFieldUnitEntry_020a693c(FieldUnit *unit, int index, const UnitRecord *src)
{
    MIi_CpuCopyFast_01ff878c(src, &unit->entries[index], sizeof(UnitRecord));
}
