#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s32 GetBoundedEntryField(s32 arg);
extern VecFx32 ActivateSpawnUnit(void *unit, int slot);
extern void VEC_Subtract(void *buf, u32 size, u32 dest);

void func_ov030_020bcec0(u32 base, u32 source, u32 record)
{
    s32 decodedSize;
    VecFx32 tempBuf;

    decodedSize = GetBoundedEntryField((s32)*(s8 *)(base + 0x3c));
    if (*(s8 *)(base + 0x3f) == 0) {
        *(u8 *)(base + 0x40) = 0;
    }
    tempBuf = ActivateSpawnUnit((void *)base, (int)source);
    if (*(s8 *)(base + 0x3f) < *(s8 *)(base + 0x3e)) {
        *(u8 *)(base + 0x1b0) = 1;
        *(u8 *)(base + 0x1a0) = 0;
        *(u32 *)(base + 0x1a4) = 0;
        *(u32 *)(base + 0x1b4) = 0;
        *(u8 *)(base + 0x1a8) = *(u8 *)(record + 4);
        *(u8 *)(base + 0x1a9) = *(u8 *)(record + 5);
        *(u32 *)(base + 0x1ac) = *(u32 *)(record + 8);
        VEC_Subtract(&tempBuf, decodedSize + 0xbc, base + 0x194);
        *(s8 *)(base + 0x3f) = *(s8 *)(base + 0x3f) + 1;
    }
}
