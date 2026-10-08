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

extern int GetPrimaryElementEnabled(void);
extern void SetEntrySlotsVisible(void *manager, int element, BOOL visible);
extern int FindWidgetById(void *manager, int elementId);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern void RuntimeState_SetCondition(int value);
extern void PlaySoundEffect(int channel, int id);
extern void UpdateRootMenuGraphics(RootMenu *menu);

void UpdateRootMenuFrame(RootMenu *menu)
{
    BOOL visible = GetPrimaryElementEnabled() == 0;

    if (menu->cursorVisible != visible) {
        SetEntrySlotsVisible(menu->objManager, menu->cursorElement, menu->cursorVisible);
        menu->cursorVisible = !menu->cursorVisible;
    }
    if (menu->mode == 3) {
        menu->revealTimer++;
        if (menu->revealTimer == 15) {
            SetEntrySlotsVisible(menu->objManager, menu->headerElement, TRUE);
            SetEntrySlotsVisible(menu->objManager, FindWidgetById(menu->objManager, 0x17), TRUE);
            menu->state = 1;
            menu->mode = 2;
            SetSecondaryElementEnabled(FALSE);
            RuntimeState_SetCondition(0);
            PlaySoundEffect(0, 2);
        }
    }
    UpdateRootMenuGraphics(menu);
}
