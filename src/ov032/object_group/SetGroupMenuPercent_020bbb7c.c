#include "nitro/types.h"

extern int contextData_020c0068[];
extern void SetGroupMenuProgress_020bb9b8(int percent);

void SetGroupMenuPercent_020bbb7c(int percent)
{
    int menu = contextData_020c0068[1];
    if (percent > 100) {
        percent = 100;
    } else if (percent < 0) {
        percent = 0;
    }
    if (percent != *(int *)(menu + 0x18)) {
        SetGroupMenuProgress_020bb9b8(percent);
        *(int *)(menu + 0x18) = percent;
    }
}
