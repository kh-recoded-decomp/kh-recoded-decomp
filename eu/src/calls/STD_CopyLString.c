#include "nitro/types.h"

extern int STD_GetStringLength(u32 str);

int STD_CopyLString(u32 dst, char *src, int size)
{
    u32 align1;
    u32 align2;
    int i;
    char *p;

    align1 = dst & 3;
    align2 = (u32)src & 3;
    p = src;
    i = 0;
    if ((align1 ^ align2) == 0) {
        if (align1 != 0) {
            for (; i + align1 < 4 && i < size - 1; i++) {
                *(char *)(dst + i) = *p;
                if (*p == 0) {
                    goto tail;
                }
                p++;
            }
        }
        if (i < size - 4) {
            do {
                u32 word = *(u32 *)(src + i);
                u32 combined = (word & 0x7f7f7f7f) + 0x7f7f7f7f | word | 0x7f7f7f7f;
                combined = ~combined;
                if (combined != 0) {
                    break;
                }
                *(u32 *)(dst + i) = word;
                i += 4;
            } while (i < size - 4);
        }
        p = src + i;
    }

    for (; i < size - 1; p++) {
        *(char *)(dst + i) = *p;
        if (*p == 0) {
            break;
        }
        i++;
    }

tail:
    if (i >= size - 1 && 0 < size) {
        *(char *)(dst + i) = 0;
    }
    if (*p != 0) {
        i += STD_GetStringLength((u32)p);
    }
    return i;
}
