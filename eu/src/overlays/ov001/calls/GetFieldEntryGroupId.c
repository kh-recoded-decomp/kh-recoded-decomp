#include "nitro/types.h"

extern u32 data_ov001_020a04bc;

int GetFieldEntryGroupId(int index)
{
    return (int)*(short *)(data_ov001_020a04bc + index * 2 + 0xa0);
}
