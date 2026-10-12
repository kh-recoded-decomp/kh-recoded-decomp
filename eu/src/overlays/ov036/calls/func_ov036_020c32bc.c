#include "nitro/types.h"

extern void SelectActiveEntry(u32 value);
extern void BackupBgGraphics(void);
extern void OpenPanel(u32 value);

u32 func_ov036_020c32bc(u32 value)
{
    SelectActiveEntry(1);
    BackupBgGraphics();
    OpenPanel(value);
    return 1;
}
