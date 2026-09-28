#include "nitro/types.h"

extern void func_020049a8(u32 param1);

void func_020049b4(int param1)
{
    int doubled = param1 * 2;

    if ((u32)doubled <= 0x10) {
        return;
    }
    func_020049a8(doubled - 0x10);
}
