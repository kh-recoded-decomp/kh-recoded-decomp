#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x30];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void GX_SetBankForBG(int bank);
extern void GX_SetBankForOBJ(int bank);
extern void GX_SetGraphicsMode(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForOBJExtPltt(int bank);
extern void GX_SetBankForBGExtPltt(int bank);
extern void func_ov002_02062504(void *value);
extern void func_ov002_02062470(void *value);

void func_ov002_02062254(void) {
    GX_SetBankForBG(1);
    GX_SetBankForOBJ(2);
    GX_SetGraphicsMode(1, 0, 0);

    *(vu16 *)0x04000008 = (*(vu16 *)0x04000008 & 0x43) | 0x84;
    *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & 0x43) | 0x184;
    *(vu16 *)0x0400000c = (*(vu16 *)0x0400000c & 0x43) | 0x214;
    *(vu16 *)0x0400000e = (*(vu16 *)0x0400000e & 0x43) | 0x31c;
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;

    GX_SetBankForOBJExtPltt(0x20);

    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & 0xffcfffef) | 0x10 | 0x200000;

    GX_SetBankForBGExtPltt(0);

    *(vu16 *)0x04000008 = (*(vu16 *)0x04000008 & ~3) | 1;
    *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & ~3) | 3;
    *(vu16 *)0x0400000c = (*(vu16 *)0x0400000c & ~3) | 2;
    *(vu16 *)0x0400000e = (*(vu16 *)0x0400000e & ~3);

    func_ov002_02062504((u8 *)data_ov002_0206c460 + 0x30);
    func_ov002_02062470((u8 *)data_ov002_0206c460 + 0x30);
}
