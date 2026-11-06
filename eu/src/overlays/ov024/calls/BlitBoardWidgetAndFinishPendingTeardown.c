#include "nitro/types.h"

typedef struct Ov024Context {
    u8 pad_00[8];
    void *handle;
} Ov024Context;

typedef struct Ov024State {
    Ov024Context *context;
    int pendingTeardown;
} Ov024State;

extern Ov024State gBoardScreenGlobals;
extern void BlitWidgetToTileTable(void *handle, int value);
extern void ReleaseOverlayResourceSlots(void);

void BlitBoardWidgetAndFinishPendingTeardown(int value) {
    BlitWidgetToTileTable(gBoardScreenGlobals.context->handle, value);
    if (gBoardScreenGlobals.pendingTeardown != 0) {
        ReleaseOverlayResourceSlots();
        gBoardScreenGlobals.pendingTeardown = 0;
    }
}
