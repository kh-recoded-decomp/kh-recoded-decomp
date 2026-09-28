#include "nitro/types.h"
#include "nitro/hw.h"

extern u32 func_0200201c(void);
extern void func_01ff8420(u32 reloadMode);
extern void func_01ff833c(void);

void OSi_DoResetSystem_01ff8310(void)
{
    while (func_0200201c() == 0) {
    }
    *(vu16 *)REG_IME_ADDR = 0;
    func_01ff8420(0);
    func_01ff833c();
}
