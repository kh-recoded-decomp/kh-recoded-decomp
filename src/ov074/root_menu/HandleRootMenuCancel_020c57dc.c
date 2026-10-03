#include "nitro/types.h"

typedef struct RootMenu {
    u8 cursor;
    u8 entryCount;
    u8 state;
    u8 mode;
    u8 pad_04[0x10 - 0x04];
    u16 revealTimer;
    u16 unlockMessage;
    u8 pad_14[0x57c - 0x14];
    void *objManager;
    u8 pad_580[0x5c0 - 0x580];
    int cursorElement;
    int headerElement;
    int frameElement;
} RootMenu;

extern int func_ov039_020bc810(void);
extern void PopStackEntry_020bc8a0(void);
extern void func_ov039_020bbf78(int a, int b, int c);
extern void SetEntrySlotsVisible_020b9580(void *manager, int element, BOOL visible);
extern int FindWidgetById_020b90a4(void *manager, int elementId);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern void func_ov039_020bc03c(int value);
extern void PlaySoundEffect_0204d924(int channel, int id);
extern int func_ov001_02064ac0(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);

void HandleRootMenuCancel_020c57dc(RootMenu *menu)
{
    int target;

    switch (menu->mode) {
    case 0:
        if (func_ov039_020bc810() == 1) {
            PopStackEntry_020bc8a0();
            target = 0;
        } else {
            target = -1;
        }
        func_ov039_020bbf78(target, -1, 1);
        break;
    case 1:
        SetEntrySlotsVisible_020b9580(menu->objManager, menu->frameElement, FALSE);
        menu->state = 1;
        menu->mode = 0;
        break;
    case 2:
        SetEntrySlotsVisible_020b9580(menu->objManager, menu->headerElement, FALSE);
        SetEntrySlotsVisible_020b9580(menu->objManager, FindWidgetById_020b90a4(menu->objManager, 0x17), FALSE);
        menu->state = 1;
        menu->mode = 0;
        SetSecondaryElementEnabled_020bc084(TRUE);
        func_ov039_020bc03c(1);
        PlaySoundEffect_0204d924(0, 1);
        if (func_ov001_02064ac0() && !IsGlobalPackedBitSet_02027304(0xfc3)) {
            SetGlobalPackedBit_02027320(0xfc3);
            menu->mode = 3;
            menu->unlockMessage = 0xc;
            menu->revealTimer = 0;
            SetSecondaryElementEnabled_020bc084(FALSE);
            func_ov039_020bc03c(0);
            return;
        }
        SetEntrySlotsVisible_020b9580(menu->objManager, menu->cursorElement, TRUE);
        return;
    case 3:
        return;
    }
    PlaySoundEffect_0204d924(0, 3);
}
