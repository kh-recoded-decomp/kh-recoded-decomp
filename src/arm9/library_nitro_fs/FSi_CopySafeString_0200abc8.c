#include "nitro/types.h"

int FSi_CopySafeString_0200abc8(char *dst, int dstLength, const char *src, int srcLength, BOOL *truncated) {
    int i;
    int count = (dstLength - 1 < srcLength) ? (dstLength - 1) : srcLength;
    for (i = 0; (i < count) && src[i]; ++i) {
        dst[i] = src[i];
    }
    if ((i < srcLength) && src[i]) {
        *truncated = TRUE;
    }
    dst[i] = '\0';
    return i;
}
