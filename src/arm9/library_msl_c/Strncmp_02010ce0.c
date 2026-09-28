#include "nitro/types.h"

int Strncmp_02010ce0(u32 str1, u32 str2, int n)
{
    u32 align1;
    u32 align2;
    int i;
    u32 word1;
    u32 b1;
    u32 b2;

    if (n != 0) {
        align1 = str1 & 3;
        align2 = str2 & 3;
        i = 0;
        if ((align1 ^ align2) == 0) {
            if (align1 != 0) {
                for (; i + align1 < 4 && i < n; i++) {
                    b1 = *(u8 *)(str1 + i);
                    b2 = *(u8 *)(str2 + i);
                    if (b1 != b2 || b1 == 0) {
                        return b1 - b2;
                    }
                }
            }
            if (i <= n - 4) {
                do {
                    u32 combined;

                    word1 = *(u32 *)(str1 + i);
                    if (word1 != *(u32 *)(str2 + i)) {
                        break;
                    }
                    combined = (word1 & 0x7f7f7f7f) + 0x7f7f7f7f | word1 | 0x7f7f7f7f;
                    combined = ~combined;
                    if (combined != 0) {
                        break;
                    }
                    i += 4;
                } while (i <= n - 4);
            }
        }

        for (; i < n; i++) {
            b1 = *(u8 *)(str1 + i);
            b2 = *(u8 *)(str2 + i);
            if (b1 != b2 || b1 == 0) {
                return b1 - b2;
            }
        }
    }

    return 0;
}
