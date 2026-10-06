#include "nitro/types.h"

extern u32 data_ov001_020a04bc;

int func_ov001_0206db8c(int index)
{
    return (int)*(short *)(data_ov001_020a04bc + index * 2 + 0xa0);
}
