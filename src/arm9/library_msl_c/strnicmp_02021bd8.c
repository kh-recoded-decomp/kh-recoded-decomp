#include "nitro/types.h"

extern u8 g_lowerCaseMap_020531e0[];

int strnicmp_02021bd8(const char *left, const char *right, int maxLength)
{
    int index;
    int leftChar;
    int rightChar;
    u8 leftLower;
    u8 rightLower;

    for (index = 0; index < maxLength; index++) {
        leftChar = *(const u8 *)left++;
        leftLower = (leftChar < 0 || leftChar >= 0x80) ? leftChar : g_lowerCaseMap_020531e0[leftChar];
        rightChar = *(const u8 *)right++;
        rightLower = (rightChar < 0 || rightChar >= 0x80) ? rightChar : g_lowerCaseMap_020531e0[rightChar];

        if (leftLower < rightLower) {
            return -1;
        }
        if (leftLower > rightLower) {
            return 1;
        }
        if (leftLower == 0) {
            return 0;
        }
    }

    return 0;
}
