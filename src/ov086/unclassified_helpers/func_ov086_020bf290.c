#include "nitro/types.h"

#pragma opt_propagation off

typedef struct {
    int values[8];
} IntTable8;

extern const IntTable8 data_ov086_020c220c;
extern const IntTable8 data_ov086_020c224c;
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);

int func_ov086_020bf290(int index)
{
    IntTable8 widths = data_ov086_020c220c;
    IntTable8 offsets = data_ov086_020c224c;
    int setCount = 0;
    u32 bits = ReadSessionPackedBits_02064574(offsets.values[index], widths.values[index]);
    int i;

    for (i = 0; i < widths.values[index]; i++) {
        if (bits & (1 << i)) {
            setCount++;
        }
    }
    return setCount;
}
