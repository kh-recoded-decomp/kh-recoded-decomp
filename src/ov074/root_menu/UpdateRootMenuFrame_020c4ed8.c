#include "nitro/types.h"

typedef struct RootMenu {
    u8 cursor;
    u8 entryCount;
    u8 state;
    u8 mode;
    u8 pad_04;
    u8 cursorVisible;
    u8 pad_06[0x10 - 0x06];
    u16 revealTimer;
    u8 pad_12[0x57c - 0x12];
    void *objManager;
    u8 pad_580[0x5c0 - 0x580];
    int cursorElement;
    int headerElement;
} RootMenu;

extern int func_ov039_020bc0d4(void);
extern void SetEntrySlotsVisible_020b9580(void *manager, int element, BOOL visible);
extern int FindWidgetById_020b90a4(void *manager, int elementId);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern void func_ov039_020bc03c(int value);
extern void PlaySoundEffect_0204d924(int channel, int id);
extern void UpdateRootMenuGraphics_020c5474(RootMenu *menu);

void UpdateRootMenuFrame_020c4ed8(RootMenu *menu)
{
    BOOL visible = func_ov039_020bc0d4() == 0;

    if (menu->cursorVisible != visible) {
        SetEntrySlotsVisible_020b9580(menu->objManager, menu->cursorElement, menu->cursorVisible);
        menu->cursorVisible = !menu->cursorVisible;
    }
    if (menu->mode == 3) {
        menu->revealTimer++;
        if (menu->revealTimer == 15) {
            SetEntrySlotsVisible_020b9580(menu->objManager, menu->headerElement, TRUE);
            SetEntrySlotsVisible_020b9580(menu->objManager, FindWidgetById_020b90a4(menu->objManager, 0x17), TRUE);
            menu->state = 1;
            menu->mode = 2;
            SetSecondaryElementEnabled_020bc084(FALSE);
            func_ov039_020bc03c(0);
            PlaySoundEffect_0204d924(0, 2);
        }
    }
    UpdateRootMenuGraphics_020c5474(menu);
}
