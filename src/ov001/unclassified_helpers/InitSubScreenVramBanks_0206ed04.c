#include "nitro/types.h"

extern void GX_SetBankForBG_02008358(u32 mask);
extern void GX_SetBankForSubBG_02008a98(u32 mask);
extern void GX_SetBankForSubOBJExtPltt_02008c24(u32 mask);
extern void GX_SetBankForSubOBJ_02008b34(u32 mask);
extern void func_02029bfc(void);
extern void func_ov001_0206ec3c(void);
extern void func_ov001_0206ec80(void);

void InitSubScreenVramBanks_0206ed04(void)
{
    func_02029bfc();
    GX_SetBankForBG_02008358(0x10);
    GX_SetBankForSubBG_02008a98(0x80);
    GX_SetBankForSubOBJ_02008b34(0x100);
    GX_SetBankForSubOBJExtPltt_02008c24(0);
    func_ov001_0206ec80();
    func_ov001_0206ec3c();
}
