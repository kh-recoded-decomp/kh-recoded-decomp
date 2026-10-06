#include "nitro/types.h"

extern void MIi_CpuCopyFast(u32 dest, u32 src, u32 size);
extern void DC_FlushAll(void);
extern void GX_LoadBGPltt(u32 dest, u32 value, u32 size);
extern void GX_LoadBG3Char(u32 dest, u32 value, u32 size);
extern s32 NNS_G2dGetUnpackedBGCharacterData(u32 resourceManager, s32 *outPayload);
extern s32 GetClampedPaletteSlot(void);
extern void func_ov001_0206ed8c(u16 flags);

void func_ov001_0206efac(s32 context, u32 resourceManager, u32 unused1, u32 unused2)
{
    s32 slotIndex;
    s32 payload;
    u32 unusedCopy;

    *(u32 *)(context + 0x480) &= 0xffff7fff;
    unusedCopy = unused2;
    NNS_G2dGetUnpackedBGCharacterData(resourceManager, &payload);
    MIi_CpuCopyFast(*(u32 *)(payload + 0x14), *(u32 *)(context + 0x460), 0x80);
    MIi_CpuCopyFast(*(u32 *)(payload + 0x14) + 0x80, *(u32 *)(context + 0x468), 0x80);
    MIi_CpuCopyFast(*(u32 *)(payload + 0x14) + 0x100, *(u32 *)(context + 0x464), 0x80);
    DC_FlushAll();
    GX_LoadBG3Char(*(u32 *)(payload + 0x14) + 0x180, 0x5900, *(u32 *)(payload + 0x10) - 0x180);
    slotIndex = GetClampedPaletteSlot();
    GX_LoadBGPltt(*(u32 *)(context + 0x470) + slotIndex * 0x20, 0x100, 0x20);
    func_ov001_0206ed8c(*(u16 *)(context + 0x476));
}
