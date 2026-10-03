#include "nitro/types.h"

typedef struct SlotMenu SlotMenu;

typedef struct MenuCallback {
    void (*handler)(SlotMenu *menu);
    SlotMenu *context;
} MenuCallback;

struct SlotMenu {
    u8 pad_00000[0x11c04];
    MenuCallback onReturn;
};

extern void *func_ov039_020bc1bc(void);
extern void SetWidgetRootTouchEnabled_020b984c(void *root, BOOL enabled);
extern void SlotMenu_CommitSlotEdit_020c8908(SlotMenu *menu);

void SlotMenu_LockTouchUntilCommit_020c88dc(SlotMenu *menu, BOOL unused)
{
    MenuCallback callback;

    SetWidgetRootTouchEnabled_020b984c(func_ov039_020bc1bc(), FALSE);
    callback.handler = SlotMenu_CommitSlotEdit_020c8908;
    callback.context = menu;
    menu->onReturn = callback;
}
