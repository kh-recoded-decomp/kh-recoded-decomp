#include "nitro/types.h"

#define REG_BG2OFS (*(volatile u32 *)0x04000018)

extern void func_ov077_020c57f4(void *work, BOOL shifted);
extern void func_ov077_020c5510(void *work, BOOL shifted);

static inline void G2_SetBG2Offset(int hOffset, int vOffset)
{
    REG_BG2OFS = (u32)((hOffset & 0x1ff) | ((vOffset & 0x1ff) << 16));
}

void SetPanelShifted_020c5618(void *work, BOOL shifted)
{
    int offset;

    if (shifted) {
        offset = 0x20;
    } else {
        offset = 0;
    }
    G2_SetBG2Offset(offset, 0);
    func_ov077_020c57f4(work, shifted);
    func_ov077_020c5510(work, shifted);
}
