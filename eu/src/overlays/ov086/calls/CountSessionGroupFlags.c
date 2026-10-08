#include "nitro/types.h"

#pragma opt_propagation off

typedef struct {
    int values[8];
} IntTable8;

extern const IntTable8 data_ov086_020c222c;
extern const IntTable8 data_ov086_020c226c;
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);

int CountSessionGroupFlags(int index)
{
    IntTable8 widths = data_ov086_020c222c;
    IntTable8 offsets = data_ov086_020c226c;
    int setCount = 0;
    u32 bits = ReadSessionPackedBits(offsets.values[index], widths.values[index]);
    int i;

    for (i = 0; i < widths.values[index]; i++) {
        if (bits & (1 << i)) {
            setCount++;
        }
    }
    return setCount;
}
