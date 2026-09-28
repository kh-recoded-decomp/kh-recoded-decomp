#include "nitro/types.h"

extern u32 func_02006630(void);
extern void func_02006640(void);
extern void func_020108a0(u32 param0, u32 param1, u32 param2, u32 param3);

void func_020109e4(int flagIn)
{
    u32 flag = flagIn;
    if (flagIn != 1) {
        flag = 0;
        if (func_02006630() != 0) {
            func_02006640();
        }
    }
    func_020108a0(flag, 0, 0, 1);
}
