#include "nitro/types.h"
#pragma opt_propagation off

typedef struct BgGraphics {
    u8 pad00[0xc];
    s32 windowMask;
    void *bg2Screen;
    void *bg3Screen;
    void *charData;
    void *palette;
} BgGraphics;

extern BgGraphics *data_ov036_020ca204;
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, s32 alignment);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);
extern void *G2_GetBG2CharPtr(void);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_IME (*(vu16 *)0x04000208)

static inline u16 DisableMasterInterrupts(void)
{
    u16 enabled = REG_IME;
    REG_IME = 0;
    return enabled;
}

static inline void RestoreMasterInterrupts(u16 enabled)
{
    if (enabled) {
        /* The original MMIO sequence reads IME before re-enabling it. */
        (void)REG_IME;
        REG_IME = 1;
    }
}

/* Save the main-engine BG2/BG3 maps, shared character data and BG palette. */
void BackupBgGraphics(void)
{
    BgGraphics *graphics = data_ov036_020ca204;
    u16 enabled;
    void *buffer;

    graphics->windowMask = (REG_DISPCNT & 0xe000) >> 13;
    enabled = DisableMasterInterrupts();

    graphics->bg2Screen = NNS_FndAllocFromDefaultExpHeapEx(0x800, -32);
    buffer = graphics->bg2Screen;
    MIi_CpuCopyFast(G2_GetBG2ScrPtr(), buffer, 0x800);

    graphics->bg3Screen = NNS_FndAllocFromDefaultExpHeapEx(0x800, -32);
    buffer = graphics->bg3Screen;
    MIi_CpuCopyFast(G2_GetBG3ScrPtr(), buffer, 0x800);

    buffer = graphics->charData = NNS_FndAllocFromDefaultExpHeapEx(0x10000, -32);
    MIi_CpuCopyFast(G2_GetBG2CharPtr(), buffer, 0x10000);

    buffer = NNS_FndAllocFromDefaultExpHeapEx(0x200, -32);
    graphics->palette = buffer;
    MIi_CpuCopyFast((const void *)0x05000000, buffer, 0x200);

    RestoreMasterInterrupts(enabled);
}
