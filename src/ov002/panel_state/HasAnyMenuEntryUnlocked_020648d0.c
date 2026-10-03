#include "nitro/types.h"

extern int func_ov002_02066c78(int kind, int index, int arg2, int arg3);

BOOL HasAnyMenuEntryUnlocked_020648d0(void)
{
    int i = 0;
    int count = func_ov002_02066c78(1, 0, 0, 0);
    int number;

    count = count + (count + (count + 1) / 10 + 1) / 10;
    for (; i < count; i++) {
        number = i + 1;
        if (number % 10 != 0) {
            if (func_ov002_02066c78(0xb, i - number / 10, 0, 0)) {
                return TRUE;
            }
        } else if (func_ov002_02066c78(9, number, 0, 0)) {
            return TRUE;
        }
    }
    return FALSE;
}
