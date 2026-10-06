#include "nitro/types.h"

extern void GX_LoadBG3Char(u32 arg1, u32 arg2, u32 arg3);
extern void NNS_G2dGetUnpackedBGCharacterData(u32 tag, s32 *out);
extern u32 func_ov027_020ba1f8();
extern void func_ov027_020ba200(u32 entry, u32 flag);

void func_ov001_02078cf8(u32 entry, u32 unused1, u32 unused2, u32 unused3)
{
    u32 tag;
    s32 resource;
    u32 unused;

    unused = unused3;
    tag = func_ov027_020ba1f8();
    NNS_G2dGetUnpackedBGCharacterData(tag, &resource);
    GX_LoadBG3Char(*(u32 *)(resource + 0x14), 0x800, *(u32 *)(resource + 0x10));
    func_ov027_020ba200(entry, 1);
}
