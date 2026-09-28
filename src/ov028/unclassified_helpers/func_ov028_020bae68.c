#include "nitro/types.h"

extern u32 g_fieldContext_020bb380;
extern void func_020360a0(u32 size);
extern void func_ov001_020668e4(void);
extern void func_ov001_02067d80(u32 size);
extern void func_ov001_0206d95c(u32 size);
extern void func_ov001_0207ecc4(u32 size);
extern void func_ov001_02087694(u32 size);

void func_ov028_020bae68(s32 mode)
{
    u32 budget = 0x1000;

    if ((*(u16 *)(g_fieldContext_020bb380 + 6) & 0x40) != 0) {
        budget = 0x100;
    }
    if (mode == 0) {
        func_ov001_02067d80(0x1000);
        func_ov001_0207ecc4(0x1000);
    }
    func_ov001_0206d95c(budget);
    if (mode == 0) {
        func_ov001_02087694(budget);
        func_ov001_020668e4();
    }
    func_020360a0(0x1000);
}
