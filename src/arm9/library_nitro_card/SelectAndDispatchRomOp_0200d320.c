#include "nitro/types.h"

extern void CARD_UnlockRom_02009198(int id);
extern void func_02009150(u16 value);

typedef struct {
    void *pad_00;
    u32 unk_04;
} RomState;

extern RomState data_02057b1c;

u32 SelectAndDispatchRomOp_0200d320(void *unused, int mode)
{
    switch (mode) {
    case 9:
        func_02009150((u16)data_02057b1c.unk_04);
        return 0;
    case 10:
        CARD_UnlockRom_02009198((u16)data_02057b1c.unk_04);
        return 0;
    case 1:
        return 4;
    default:
        return 0x102;
    }
}
