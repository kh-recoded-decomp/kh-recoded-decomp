#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x30];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void GX_SetBankForSubBG(int bank);
extern void GX_SetBankForSubOBJ(int bank);
extern void GXS_SetGraphicsMode(int enabled);
extern void GX_SetBankForSubOBJExtPltt(int bank);
extern void GX_SetBankForSubBGExtPltt(int bank);
extern void CreatePanelTextLayer6(void *value);
extern void CreatePanelTextLayer(void *value);

void func_ov002_02062368(void) {
    GX_SetBankForSubBG(4);
    GX_SetBankForSubOBJ(8);
    GXS_SetGraphicsMode(0);

    *(vu16 *)0x04001008 = (*(vu16 *)0x04001008 & 0x43) | 0x84;
    *(vu16 *)0x0400100a = (*(vu16 *)0x0400100a & 0x43) | 0x184;
    *(vu16 *)0x0400100c = (*(vu16 *)0x0400100c & 0x43) | 0x214;
    *(vu16 *)0x0400100e = (*(vu16 *)0x0400100e & 0x43) | 0x31c;
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;

    GX_SetBankForSubOBJExtPltt(0x100);

    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & 0xffcfffef) | 0x10 | 0x200000;

    GX_SetBankForSubBGExtPltt(0);

    *(vu16 *)0x04001008 = (*(vu16 *)0x04001008 & ~3) | 1;
    *(vu16 *)0x0400100a = (*(vu16 *)0x0400100a & ~3) | 3;
    *(vu16 *)0x0400100c = (*(vu16 *)0x0400100c & ~3) | 2;
    *(vu16 *)0x0400100e = (*(vu16 *)0x0400100e & ~3);

    CreatePanelTextLayer6((u8 *)data_ov002_0206c460 + 0x30);
    CreatePanelTextLayer((u8 *)data_ov002_0206c460 + 0x30);
}
