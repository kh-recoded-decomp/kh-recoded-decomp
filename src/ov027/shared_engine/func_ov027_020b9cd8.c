#include "nitro/types.h"

extern int func_ov027_020b9948(int pool, u32 key, u32 *outBuffer);
extern void func_01ff8684(u32 fillValue, void *dest, u32 size);

u32 func_ov027_020b9cd8(int pool, u32 key, u32 unused, u32 extra) {
    int found;
    u32 outValue;
    u32 extraCopy;

    extraCopy = extra;
    found = func_ov027_020b9948(pool, key, &outValue);
    if (found != 0) {
        func_01ff8684(0, (void *)found, (u32)*(u16 *)(pool + 0xc) << 1);
        return outValue;
    }
    return 0xffffffff;
}
