#include "nitro/types.h"

/* Shared engine per-overlay setup sequence. */

extern void func_ov050_020c35e0(void);
extern void func_ov050_020c3888(u32 context, u32 data);
extern void func_ov050_020c39dc(u32 context, u32 data);
extern void func_ov050_020c3b10(u32 context, u32 data);

u32 func_ov050_020c3510(u32 context, u32 data)
{
    func_ov050_020c35e0();
    func_ov050_020c3888(context, data);
    func_ov050_020c39dc(context, data);
    func_ov050_020c3b10(context, data);
    return 0;
}
