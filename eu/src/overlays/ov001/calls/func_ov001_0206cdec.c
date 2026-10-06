#include "nitro/types.h"

void func_ov001_0206cdec(u32 *record, int extended)
{
    record[0] = 0;
    record[1] = 0;
    record[2] = 0;
    if (extended != 0) {
        record[3] = 0;
        record[4] = 0xffffffff;
    }
}
