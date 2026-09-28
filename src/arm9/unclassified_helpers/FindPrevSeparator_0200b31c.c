#include "nitro/types.h"

extern int FindPrevCharBoundary_0200b288(u8 *str, int pos);

int FindPrevSeparator_0200b31c(u8 *str, int pos) {
    int i;
    do {
        i = FindPrevCharBoundary_0200b288(str, pos);
        if (i < 0) break;
        if (str[i] == '/' || str[i] == '\\') break;
        pos = i;
    } while (1);
    return i;
}
