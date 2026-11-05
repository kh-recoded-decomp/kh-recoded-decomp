#include "nitro/types.h"

extern u32 data_ov001_020a04bc;

u32 GetManagedActorCount(void)
{
    if (data_ov001_020a04bc == 0) {
        return 0;
    }
    return *(u32 *)(data_ov001_020a04bc + 0x7c);
}
