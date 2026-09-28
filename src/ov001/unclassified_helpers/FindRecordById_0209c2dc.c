#include "nitro/types.h"

extern u32 func_ov001_0209c040();

u32 FindRecordById_0209c2dc(int id)
{
    u32 record;

    if (id == 0) {
        return 0;
    }
    record = func_ov001_0209c040((int)(short)id);
    return record;
}
