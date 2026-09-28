#include "nitro/types.h"

extern const s16 data_0205356c[];

u16 Math_AsinIdx_0202aaa8(int sine)
{
    int low;
    int high;
    int middle;
    s16 target;

    if (sine >= 0) {
        low = 0;
        high = 0x400;
    } else {
        low = 0xc00;
        high = 0x1000;
    }
    target = (s16)sine;

    while (low <= high) {
        middle = (low + high) / 2;
        if (target == data_0205356c[middle]) {
            break;
        }
        if (data_0205356c[middle] < target) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    return (u16)(((middle * 2) << 16) / 0x2000);
}
