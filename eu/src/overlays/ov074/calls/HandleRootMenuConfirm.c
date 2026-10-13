#include "src/overlays/ov074/RootMenu.h"

extern void PushStackEntry(int value);
extern void StartSubScene(int sceneId, int fadeFrames, BOOL markPending);
extern void SetEntrySlotsVisible(void *manager, int element, BOOL visible);
extern void PlaySoundEffect(int channel, int id);
extern void SetEventStateFlagCa34(void);
extern int FindWidgetById(void *manager, int id);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern void RuntimeState_SetCondition(int value);
extern BOOL IsBattleModeOne(void);
extern BOOL IsGlobalPackedBitSet(int index);
extern void SetGlobalPackedBit(int index);

void HandleRootMenuConfirm(RootMenu *menu)
{
    switch (menu->mode) {
    case 0: {
        int scene = menu->entries[menu->cursor].sceneId;
        if (scene > -2) {
            u32 mask;
            if (scene >= 0) {
                mask = 1u << scene;
            } else {
                mask = 0;
            }
            PushStackEntry(menu->cursor);
            StartSubScene(scene, -1, (mask & 0x40a0f) != 0);
        } else {
            SetEntrySlotsVisible(menu->objManager, menu->frameElement, TRUE);
            menu->optionCursor = 1;
            menu->state = 1;
            menu->mode = 1;
        }
        PlaySoundEffect(0, 1);
        return;
    }
    case 1:
        if (menu->optionCursor == 0) {
            SetEventStateFlagCa34();
            StartSubScene(-1, -1, TRUE);
        } else {
            SetEntrySlotsVisible(menu->objManager, menu->frameElement, FALSE);
            menu->state = 1;
            menu->mode = 0;
        }
        PlaySoundEffect(0, 1);
        return;
    case 2:
        SetEntrySlotsVisible(menu->objManager, menu->headerElement, FALSE);
        SetEntrySlotsVisible(menu->objManager, FindWidgetById(menu->objManager, 0x17), FALSE);
        menu->state = 1;
        menu->mode = 0;
        SetSecondaryElementEnabled(TRUE);
        RuntimeState_SetCondition(1);
        PlaySoundEffect(0, 1);
        if (IsBattleModeOne() && !IsGlobalPackedBitSet(0xfc3)) {
            SetGlobalPackedBit(0xfc3);
            menu->mode = 3;
            menu->unlockMessage = 12;
            menu->revealTimer = 0;
            SetSecondaryElementEnabled(FALSE);
            RuntimeState_SetCondition(0);
            return;
        }
        SetEntrySlotsVisible(menu->objManager, menu->cursorElement, TRUE);
        return;
    }
}
