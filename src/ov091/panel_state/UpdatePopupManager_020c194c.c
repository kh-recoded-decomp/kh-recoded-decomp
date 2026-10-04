#include "nitro/types.h"

typedef struct {
    s32 x;
    s32 y;
    u16 *text;
    s32 param;
} PopupMessage;

typedef struct {
    s32 state;
    u8 pad_04[0x5c];
} PopupWindow;

typedef struct {
    u8 pad_00[0x2c];
    PopupWindow window;
    PopupMessage queue[30];
    s32 queueCount;
} PopupManager;

typedef void (*PopupStateFunc)(PopupWindow *window);

extern PopupManager *g_popupManager_020c373c;
extern PopupStateFunc data_ov091_020c29f0[];
extern s32 func_ov091_020c2794(PopupWindow *window);
extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern void SetPopupState_020c2784(PopupWindow *window, s32 state);

int UpdatePopupManager_020c194c(void)
{
    PopupManager *manager = g_popupManager_020c373c;
    PopupStateFunc handler = data_ov091_020c29f0[func_ov091_020c2794(&manager->window)];

    if (handler != NULL) {
        handler(&manager->window);
    }
    if (g_popupManager_020c373c->queueCount > 0 && func_ov091_020c2794(&manager->window) >= 0) {
        MIi_CpuClearFast_01ff8740(0, &g_popupManager_020c373c->window, sizeof(PopupWindow));
        SetPopupState_020c2784(&g_popupManager_020c373c->window, 1);
    }
    return 0;
}
