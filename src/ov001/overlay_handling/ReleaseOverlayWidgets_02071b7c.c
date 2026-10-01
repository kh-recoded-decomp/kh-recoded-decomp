#include "nitro/types.h"

typedef struct OverlayState {
    u8 pad[0x42c];
    u32 handle;
    u8 pad430[0x50];
    u32 released : 1;
    u32 unk480 : 31;
    u8 pad484[0x180];
    int selection;
} OverlayState;

typedef struct OverlayGlobals {
    u32 unk0;
    OverlayState *state;
} OverlayGlobals;

extern OverlayGlobals data_ov001_020a04a4;
extern int func_ov001_0207123c(void);
extern void PXI_Init_0202a638(u32 handle);
extern void func_ov027_020b9d18(int widgets, int layer);
extern void func_02029f98(int processor, int overlayId);
extern char OVERLAY_45_ID_0000002d[];

void ReleaseOverlayWidgets_02071b7c(void) {
    OverlayState *state = data_ov001_020a04a4.state;
    int widgets = func_ov001_0207123c();

    if (state->handle != 0) {
        PXI_Init_0202a638(state->handle);
        state->handle = 0;
        state->released = 1;
        state->selection = -2;
        func_ov027_020b9d18(widgets, 9);
        func_ov027_020b9d18(widgets, 10);
        func_ov027_020b9d18(widgets, 11);
        func_02029f98(0, (int)OVERLAY_45_ID_0000002d);
    }
}
