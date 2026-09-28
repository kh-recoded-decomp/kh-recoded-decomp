#include "nitro/types.h"

extern s32 func_ov001_0206db5c(s32 arg);
extern void func_ov021_020aed24(void *out, u32 base, u32 source);
extern void func_01ff9e3c(void *buf, u32 size, u32 dest);

void func_ov030_020bcea0(u32 base, u32 source, u32 record)
{
    s32 decodedSize;
    u8 tempBuf[12];

    decodedSize = func_ov001_0206db5c((s32)*(s8 *)(base + 0x3c));
    if (*(s8 *)(base + 0x3f) == 0) {
        *(u8 *)(base + 0x40) = 0;
    }
    func_ov021_020aed24(tempBuf, base, source);
    if (*(s8 *)(base + 0x3f) < *(s8 *)(base + 0x3e)) {
        *(u8 *)(base + 0x1b0) = 1;
        *(u8 *)(base + 0x1a0) = 0;
        *(u32 *)(base + 0x1a4) = 0;
        *(u32 *)(base + 0x1b4) = 0;
        *(u8 *)(base + 0x1a8) = *(u8 *)(record + 4);
        *(u8 *)(base + 0x1a9) = *(u8 *)(record + 5);
        *(u32 *)(base + 0x1ac) = *(u32 *)(record + 8);
        func_01ff9e3c(tempBuf, decodedSize + 0xbc, base + 0x194);
        *(s8 *)(base + 0x3f) = *(s8 *)(base + 0x3f) + 1;
    }
}
