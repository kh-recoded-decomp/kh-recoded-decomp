#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x8c];
    u32 slotCount;
    u8 slotModes[0x10];
    u8 slotFlags[0x10];
} SlotTable;

extern void MIi_CpuFill8_01ff8830(void *dest, u8 data, u32 size);

void ResetSlotFlags_020a1b18(SlotTable *table, u32 count) {
    table->slotCount = count;
    MIi_CpuFill8_01ff8830(table->slotModes, 0x1f, count);
    MIi_CpuFill8_01ff8830(table->slotFlags, 0, count);
}
