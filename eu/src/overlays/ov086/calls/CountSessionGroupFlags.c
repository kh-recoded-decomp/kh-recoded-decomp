#include "nitro/types.h"

#pragma opt_propagation off

typedef struct {
    int values[8];
} IntTable8;

extern const IntTable8 gRecordGroupFlagFieldWidths;
extern const IntTable8 gRecordGroupFlagFieldOffsets;
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);

int CountSessionGroupFlags(int index)
{
    IntTable8 widths = gRecordGroupFlagFieldWidths;
    IntTable8 offsets = gRecordGroupFlagFieldOffsets;
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
