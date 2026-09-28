#include "nitro/types.h"

extern u32 g_fieldContext_020bb380;
extern s32 func_ov001_02063404(void);
extern void func_ov001_0207efac(void);

u32 func_ov028_020ba6b4(void)
{
    s32 result = func_ov001_02063404();

    if ((result == 1) && (*(s8 *)(g_fieldContext_020bb380 + 8) != 3)) {
        *(u8 *)(g_fieldContext_020bb380 + 8) = 0;
    }
    func_ov001_0207efac();
    *(u16 *)(g_fieldContext_020bb380 + 6) = *(u16 *)(g_fieldContext_020bb380 + 6) | 0x8000;
    return 2;
}
