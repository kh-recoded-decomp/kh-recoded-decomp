#include "nitro/types.h"

typedef struct StatusMenu {
    s8 mode;
    u8 pad_01;
    u8 refreshCount;
    u8 flags;
    u8 pad_04[0x10];
    BOOL busy;
} StatusMenu;

extern void func_ov073_020c1a00(StatusMenu *menu);
extern void SetStatusElementVisible_020beb5c(int elementId, BOOL visible);
extern void SetScreenBrightness_020bc648(int brightness);
extern void SetPrimaryElementEnabled_020bc054(BOOL enabled);
extern void func_ov039_020bc03c(int arg);

void AddStatusMenuFlags_020c1be0(StatusMenu *menu, int flags)
{
    BOOL busy;

    menu->flags |= (u8)flags;
    busy = TRUE;
    if (!(menu->flags & 1) && (menu->flags != 2 || menu->mode == 0)) {
        busy = FALSE;
    }
    menu->busy = busy;
    if (busy) {
        func_ov073_020c1a00(menu);
    }
    menu->refreshCount++;
    if (menu->flags & 2) {
        SetStatusElementVisible_020beb5c(3, TRUE);
        SetScreenBrightness_020bc648(-8);
        SetPrimaryElementEnabled_020bc054(FALSE);
    }
    if (((*(vu16 *)0x04000304 & 0x8000) >> 15) == 0) {
        func_ov039_020bc03c(0);
    }
}
