#include "nitro/types.h"

extern u16 *UpdateFieldWidgetLayer(int layer);
extern void MIi_CpuClear16(u16 value, void *dest, u32 size);

/* Clears rows 1 and 2 of the caption's tile map (widget layer 0xb). */
void ClearStageCaptionRows(void)
{
    int row;
    u16 *map = UpdateFieldWidgetLayer(0xb);

    for (row = 1; row < 3; row++) {
        MIi_CpuClear16(0, map + row * 0x20, 0x40);
    }
}
