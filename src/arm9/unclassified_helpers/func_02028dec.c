#include "nitro/types.h"

typedef struct Counter {
    u8 pad_00[2];
    u16 value;
} Counter;

extern Counter data_0205ffc4;

void func_02028dec(u8 *flag)
{
    if (*flag == 0) {
        *flag = *flag + 1;
        data_0205ffc4.value += 1;
    }
}
