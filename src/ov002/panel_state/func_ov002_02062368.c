#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x30];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void GX_SetBankForSubBG_02008a98(int bank);
extern void GX_SetBankForSubOBJ_02008b34(int bank);
extern void func_0200672c(int enabled);
extern void GX_SetBankForSubOBJExtPltt_02008c24(int bank);
extern void GX_SetBankForSubBGExtPltt_02008ba4(int bank);
extern void func_ov002_02062638(void *value);
extern void func_ov002_020625a0(void *value);

void func_ov002_02062368(void) {
    GX_SetBankForSubBG_02008a98(4);
    GX_SetBankForSubOBJ_02008b34(8);
    func_0200672c(0);

    *(vu16 *)0x04001008 = (*(vu16 *)0x04001008 & 0x43) | 0x84;
    *(vu16 *)0x0400100a = (*(vu16 *)0x0400100a & 0x43) | 0x184;
    *(vu16 *)0x0400100c = (*(vu16 *)0x0400100c & 0x43) | 0x214;
    *(vu16 *)0x0400100e = (*(vu16 *)0x0400100e & 0x43) | 0x31c;
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;

    GX_SetBankForSubOBJExtPltt_02008c24(0x100);

    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & 0xffcfffef) | 0x10 | 0x200000;

    GX_SetBankForSubBGExtPltt_02008ba4(0);

    *(vu16 *)0x04001008 = (*(vu16 *)0x04001008 & ~3) | 1;
    *(vu16 *)0x0400100a = (*(vu16 *)0x0400100a & ~3) | 3;
    *(vu16 *)0x0400100c = (*(vu16 *)0x0400100c & ~3) | 2;
    *(vu16 *)0x0400100e = (*(vu16 *)0x0400100e & ~3);

    func_ov002_02062638((u8 *)g_panelState_0206c460 + 0x30);
    func_ov002_020625a0((u8 *)g_panelState_0206c460 + 0x30);
}
