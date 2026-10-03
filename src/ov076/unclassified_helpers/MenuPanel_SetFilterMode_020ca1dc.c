#include "nitro/types.h"

typedef struct MenuPanel {
    u8 pad_0000[0x18];
    void *container;
    u8 pad_001C[4];
    u16 filterMode;
    u8 pad_0022[0x4d78 - 0x22];
    u16 firstIndex;
    u8 pad_4D7A[0x4d84 - 0x4d7a];
    u16 topIndex;
    s16 cursorIndex;
    s16 lastCursorIndex;
} MenuPanel;

extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern u16 MenuPanel_ApplyCategoryFilter_020c9c14(MenuPanel *panel, int mode);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b96a0(void *container, void *element, u16 mode);
extern void func_ov076_020c9d98(MenuPanel *panel);

BOOL MenuPanel_SetFilterMode_020ca1dc(MenuPanel *panel, int mode)
{
    BOOL changed;

    if ((panel->filterMode != mode && MenuPanel_ApplyCategoryFilter_020c9c14(panel, mode) != 0) || mode == 1) {
        changed = TRUE;
    } else {
        changed = FALSE;
    }
    if (changed) {
        PlaySoundEffect_0204d924(1, 2);
        panel->filterMode = mode;
        panel->topIndex = panel->firstIndex;
        panel->cursorIndex = 0;
        panel->lastCursorIndex = panel->cursorIndex;
        func_ov027_020b96a0(panel->container, func_ov027_020b90a4(panel->container, 0x1b), mode);
        func_ov076_020c9d98(panel);
    } else {
        PlaySoundEffect_0204d924(1, 4);
    }
    return changed;
}
