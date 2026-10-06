#include "nitro/types.h"

extern void SelectActiveEntry(u32 value);
extern void func_ov036_020c3104(void);
extern void OpenPanel(u32 value);

u32 func_ov036_020c32bc(u32 value)
{
    SelectActiveEntry(1);
    func_ov036_020c3104();
    OpenPanel(value);
    return 1;
}
