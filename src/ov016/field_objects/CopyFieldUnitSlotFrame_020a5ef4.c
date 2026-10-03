#include "nitro/types.h"

typedef struct {
    u8 data[0x1e0];
} SlotFrame;

typedef struct {
    u8 pad_00[0xc4];
    void *slotRecords;
} FieldUnit;

typedef struct {
    u8 pad_00[4];
    FieldUnit *unit;
} FieldLink;

extern SlotFrame *GetFieldUnitSlotRecord_020a5cfc(FieldUnit *unit, void *records);
extern void MIi_CpuCopyFast_01ff878c(const void *src, void *dst, u32 size);

void CopyFieldUnitSlotFrame_020a5ef4(FieldLink *link, int index, void *dest)
{
    MIi_CpuCopyFast_01ff878c(&GetFieldUnitSlotRecord_020a5cfc(link->unit, link->unit->slotRecords)[index], dest,
                             sizeof(SlotFrame));
}
