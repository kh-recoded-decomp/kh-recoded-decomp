#include "nitro/types.h"

extern int GetTileTableRow(int pool, u32 key, u32 *outBuffer);
extern void MIi_CpuClear16(u32 fillValue, void *dest, u32 size);

u32 func_ov027_020b9cf8(int pool, u32 key, u32 unused, u32 extra) {
    int found;
    u32 outValue;
    u32 extraCopy;

    extraCopy = extra;
    found = GetTileTableRow(pool, key, &outValue);
    if (found != 0) {
        MIi_CpuClear16(0, (void *)found, (u32)*(u16 *)(pool + 0xc) << 1);
        return outValue;
    }
    return 0xffffffff;
}
