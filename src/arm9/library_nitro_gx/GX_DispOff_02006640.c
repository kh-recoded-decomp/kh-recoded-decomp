#include "nitro/types.h"

extern u16 data_02056f08;
extern u16 data_02055c18;

extern void PMi_RecordPowerTick_02010b90(void);

void GX_DispOff_02006640(void)
{
    vu32 *displayControl = (vu32 *)0x04000000;
    u32 control = *displayControl;

    data_02055c18 = 0;
    data_02056f08 = (u16)((control & 0x30000) >> 16);
    *displayControl = control & ~0x30000;
    PMi_RecordPowerTick_02010b90();
}
