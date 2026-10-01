#include "nitro/types.h"

typedef struct OverlayWindow {
    void *object;
    u8 pad_04[0x2c];
    int state;
    u8 pad_34[0x1c];
    int menuId;
    int menuValue;
    u8 pad_58[0x10];
    u32 flags;
    u8 pad_6C[0x38];
    u8 overlayInfo[0x2c];
    int pendingCount;
    void *descriptor;
    void *pendingValue;
    void *currentValue;
    int fadeState;
} OverlayWindow;

extern void StartOverlay_0200bb74(void *overlay);
extern void *Obj_CreateWithTailWork_0202a47c(void *descriptor, void *userData);
extern int func_02029f58(void);
extern BOOL func_ov001_0207b3cc(void);
extern void func_ov023_020b6cf4(void);
extern void func_ov023_020b6c48(u32 index, u32 value);

void StartMenuOverlayWindow_0207ac18(OverlayWindow *window)
{
    BOOL busy = TRUE;

    if (!(window->flags & 1)) {
        busy = FALSE;
    }
    if (busy) {
        return;
    }
    StartOverlay_0200bb74(window->overlayInfo);
    window->object = Obj_CreateWithTailWork_0202a47c(window->descriptor, NULL);
    window->currentValue = window->pendingValue;
    window->pendingCount = 0;
    window->descriptor = NULL;
    window->fadeState = func_02029f58();
    if (!func_ov001_0207b3cc()) {
        switch (window->menuId) {
        case -2:
            func_ov023_020b6cf4();
            break;
        case -1:
            break;
        default:
            func_ov023_020b6c48(window->menuId, window->menuValue);
            break;
        }
    }
    window->state = 3;
}
