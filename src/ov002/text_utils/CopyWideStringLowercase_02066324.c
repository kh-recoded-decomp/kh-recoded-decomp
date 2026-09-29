#include "nitro/types.h"

extern int func_ov002_02066374(const u16 *text);

void CopyWideStringLowercase_02066324(u16 *dst, const u16 *src)
{
    int length = func_ov002_02066374(src);
    int index;

    for (index = 0; index < length; index++) {
        u16 ch = src[index];
        dst[index] = ch;
        if (ch >= 'A' && ch <= 'Z') {
            dst[index] = ch + 0x20;
        }
    }
}
