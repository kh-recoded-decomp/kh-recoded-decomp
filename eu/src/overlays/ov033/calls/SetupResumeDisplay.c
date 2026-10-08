#include "nitro/types.h"

typedef struct {
    u32 address[10];
} NNSGfdFrmTexVramState;

#define REG_DISPCNT     (*(vu32 *)0x04000000)
#define REG_DISP3DCNT   (*(vu16 *)0x04000060)
#define REG_DB_DISPCNT  (*(vu32 *)0x04001000)

extern void ResetDisplayHardware(void);
extern void GX_SetBankForTex(int bank);
extern void GX_SetBankForTexPltt(int bank);
extern void NNS_GfdInitFrmTexVramManager(int numSlot, BOOL useAsDefault);
extern void NNS_GfdSetFrmTexVramState(const NNSGfdFrmTexVramState *state);
extern void NNS_GfdInitFrmPlttVramManager(int processing_mode, int install_callbacks);
extern void G3X_SetClearColor(int color, int alpha, int depth, int polygonID, BOOL fog);

void SetupResumeDisplay(void)
{
    NNSGfdFrmTexVramState state;

    ResetDisplayHardware();
    GX_SetBankForTex(0xf);
    GX_SetBankForTexPltt(0x60);

    REG_DISP3DCNT = (u16)(REG_DISP3DCNT & ~0x3002);
    REG_DISP3DCNT &= ~0x3004;
    REG_DISP3DCNT = (u16)((REG_DISP3DCNT & ~0x3000) | 8);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (0xf << 8);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | (0x1f << 8);

    NNS_GfdInitFrmTexVramManager(4, TRUE);
    state.address[1] = 0x20000;
    state.address[3] = 0x20000;
    state.address[7] = 0x20000;
    state.address[9] = 0x20000;
    state.address[0] = 0;
    state.address[2] = 0;
    state.address[4] = 0;
    state.address[5] = 0;
    state.address[6] = 0;
    state.address[8] = 0;
    NNS_GfdSetFrmTexVramState(&state);
    NNS_GfdInitFrmPlttVramManager(0x8000, 1);
    G3X_SetClearColor(0, 0x1f, 0x7fff, 0x3f, FALSE);
}
