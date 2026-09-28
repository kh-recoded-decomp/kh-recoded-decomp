#include "nitro/types.h"

extern void func_02007b70(u32 arg1, u32 arg2, u32 arg3);
extern void func_02014d38(u32 tag, s32 *out);
extern u32 func_ov027_020ba1d8();
extern void func_ov027_020ba1e0(u32 entry, u32 flag);

void func_ov001_02078cf8(u32 entry, u32 unused1, u32 unused2, u32 unused3)
{
    u32 tag;
    s32 resource;
    u32 unused;

    unused = unused3;
    tag = func_ov027_020ba1d8();
    func_02014d38(tag, &resource);
    func_02007b70(*(u32 *)(resource + 0x14), 0x800, *(u32 *)(resource + 0x10));
    func_ov027_020ba1e0(entry, 1);
}
