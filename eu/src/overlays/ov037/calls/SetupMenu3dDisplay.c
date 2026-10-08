#include "nitro/types.h"

typedef struct NNSGfdFrmTexVramState {
    u32 address[10];
} NNSGfdFrmTexVramState;

extern void ResetDisplayHardware(void);
extern void GX_SetBankForTex(int banks);
extern void GX_SetBankForTexPltt(int bank);
extern void NNS_GfdInitFrmTexVramManager(u16 numSlot, BOOL useAsDefault);
extern void NNS_GfdSetFrmTexVramState(const NNSGfdFrmTexVramState *state);
extern void NNS_GfdInitFrmPlttVramManager(int processingMode, int installCallbacks);
extern void G3X_SetClearColor(int rgb, int alpha, int depth, int polygonId, int fog);

void SetupMenu3dDisplay(void)
{
    NNSGfdFrmTexVramState state;

    ResetDisplayHardware();
    GX_SetBankForTex(0xf);
    GX_SetBankForTexPltt(0x60);
    *(vu16 *)0x04000060 = (u16)(*(vu16 *)0x04000060 & ~0x3002);
    *(vu16 *)0x04000060 &= ~0x3004;
    *(vu16 *)0x04000060 = (u16)((*(vu16 *)0x04000060 & ~0x3000) | 8);
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0xf00;
    *(vu32 *)0x04001000 = *(vu32 *)0x04001000 & ~0x1f00;
    NNS_GfdInitFrmTexVramManager(4, TRUE);
    state.address[0] = 0;
    state.address[1] = 0x20000;
    state.address[2] = 0;
    state.address[3] = 0x20000;
    state.address[4] = 0;
    state.address[5] = 0;
    state.address[6] = 0;
    state.address[7] = 0x20000;
    state.address[8] = 0;
    state.address[9] = 0x20000;
    NNS_GfdSetFrmTexVramState(&state);
    NNS_GfdInitFrmPlttVramManager(0x8000, 1);
    G3X_SetClearColor(0, 0x1f, 0x7fff, 0x3f, 0);
}
