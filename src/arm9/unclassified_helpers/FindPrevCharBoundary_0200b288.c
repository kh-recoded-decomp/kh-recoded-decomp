#include "nitro/types.h"

int FindPrevCharBoundary_0200b288(u8 *str, int pos) {
    int i = pos - 1;
    while (i > 0 && (u32)(str[i - 1] ^ 0x20) - 0xa1 < 0x3c) {
        i--;
    }
    return (pos - 1) - (((pos - 1) - i) & 1);
}
