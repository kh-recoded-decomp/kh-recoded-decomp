#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x30];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void GX_SetBankForBG_02008358(int bank);
extern void GX_SetBankForOBJ_0200855c(int bank);
extern void GX_SetGraphicsMode_020066c4(int dispMode, int bgMode, int bg0As);
extern void GX_SetBankForOBJExtPltt_02008784(int bank);
extern void GX_SetBankForBGExtPltt_0200868c(int bank);
extern void func_ov002_02062504(void *value);
extern void func_ov002_02062470(void *value);

void func_ov002_02062254(void) {
    GX_SetBankForBG_02008358(1);
    GX_SetBankForOBJ_0200855c(2);
    GX_SetGraphicsMode_020066c4(1, 0, 0);

    *(vu16 *)0x04000008 = (*(vu16 *)0x04000008 & 0x43) | 0x84;
    *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & 0x43) | 0x184;
    *(vu16 *)0x0400000c = (*(vu16 *)0x0400000c & 0x43) | 0x214;
    *(vu16 *)0x0400000e = (*(vu16 *)0x0400000e & 0x43) | 0x31c;
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1f00;

    GX_SetBankForOBJExtPltt_02008784(0x20);

    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & 0xffcfffef) | 0x10 | 0x200000;

    GX_SetBankForBGExtPltt_0200868c(0);

    *(vu16 *)0x04000008 = (*(vu16 *)0x04000008 & ~3) | 1;
    *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & ~3) | 3;
    *(vu16 *)0x0400000c = (*(vu16 *)0x0400000c & ~3) | 2;
    *(vu16 *)0x0400000e = (*(vu16 *)0x0400000e & ~3);

    func_ov002_02062504((u8 *)g_panelState_0206c460 + 0x30);
    func_ov002_02062470((u8 *)g_panelState_0206c460 + 0x30);
}
