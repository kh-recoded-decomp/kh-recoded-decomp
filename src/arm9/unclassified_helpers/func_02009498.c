#include "nitro/types.h"

extern void func_0200347c(void);
extern void func_02003488(void);

void func_02009498(u32 param1, u32 param2, u32 param3)
{
    if (param2 >= param3) {
        func_0200347c();
        return;
    }
    func_02003488();
}
