#include "nitro/types.h"

extern int func_02021e44(u32 str);
extern void func_01ff89a8(u32 src, void *dest, int len);

void func_ov001_02069de0(u32 *slot, int source, int isSecondary)
{
    int length;
    u32 text;

    text = *(u32 *)(source + 4);
    length = func_02021e44(text);
    func_01ff89a8(text, slot + 3, length);
    *(u8 *)((int)slot + length + 0xc) = 0;
    if (isSecondary != 0) {
        *slot = 0x2069dcd;
        return;
    }
    *slot = 0x2069dbd;
    return;
}
