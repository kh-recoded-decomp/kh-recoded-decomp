#include "nitro/types.h"

extern u32 data_02056fe0;
extern BOOL func_020093d0(u32 *request, int setArgs, u32 arg1, u32 arg2);

void func_0200928c(void)
{
    func_020093d0(&data_02056fe0, 0, 0, 0);
}
