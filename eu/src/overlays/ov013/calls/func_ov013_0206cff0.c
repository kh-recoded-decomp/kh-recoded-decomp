#include "nitro/types.h"

extern void SetGroupSlotsVisible(int screenBase, int paletteBase, int mode);
extern void SetPanelPhase(int index);
extern int data_ov013_02074ce0;

/* Enables panel background layers, clears busy flags. */
void func_ov013_0206cff0(void) {
    *(vu32 *)0x4000000 = (*(vu32 *)0x4000000 & ~0x1f00) | 0xd00;
    *(vu8 *)(data_ov013_02074ce0 + 0x99) |= 0x40;
    SetGroupSlotsVisible(data_ov013_02074ce0 + 0x39c, data_ov013_02074ce0 + 0xcc94, 0);
    {
        int flags = *(u8 *)(data_ov013_02074ce0 + 0x99);
        flags = flags & ~8;
        *(u8 *)(data_ov013_02074ce0 + 0x99) = (u8)flags;
    }
    {
        int flags = *(u8 *)(data_ov013_02074ce0 + 0xd259);
        flags = flags & ~1;
        *(u8 *)(data_ov013_02074ce0 + 0xd259) = (u8)flags;
    }
    *(u32 *)(data_ov013_02074ce0 + 0x2e8) = 0xffffffff;
    SetPanelPhase(0);
}
