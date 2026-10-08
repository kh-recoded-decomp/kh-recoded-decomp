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

extern OverlayGlobals data_ov001_020a04c4;
extern int func_ov001_0207123c(void);
extern void PXI_Init_0202a64c(u32 handle);
extern void ClearTileTableRowAndMarkDirty(int widgets, int layer);
extern void func_02029fac(int processor, int overlayId);
extern char OVERLAY_45_ID[];

void ReleaseOverlayWidgets(void) {
    OverlayState *state = data_ov001_020a04c4.state;
    int widgets = func_ov001_0207123c();

    if (state->handle != 0) {
        PXI_Init_0202a64c(state->handle);
        state->handle = 0;
        state->released = 1;
        state->selection = -2;
        ClearTileTableRowAndMarkDirty(widgets, 9);
        ClearTileTableRowAndMarkDirty(widgets, 10);
        ClearTileTableRowAndMarkDirty(widgets, 11);
        func_02029fac(0, (int)OVERLAY_45_ID);
    }
}
