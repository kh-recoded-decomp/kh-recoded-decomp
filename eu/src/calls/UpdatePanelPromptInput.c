#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x94];
    s32 selectedSlot;
    u8 pad_98[0x1c];
    s32 confirmed;
    s32 field_b8;
    s32 field_bc;
    u8 pad_C0[0x4];
    s32 fadePending;
} PanelState;

extern PanelState *gPanelState;
extern u32 gPreviousPanelActive;
extern u16 gPadPressedStorage;

extern void UpdateSoundAndSceneScriptSkip(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void ResetPanelFieldB8AndNotify(void);
extern void UpdatePanelPromptBlink(void);
extern void QueuePanelScreenTransferAndUpdateSound(void);
extern BOOL ToggleSelectedPanelSlot(void);
extern void RequestCurrentSceneScriptSkip(void);
extern void StopSequencePlayersFrom2(void);
extern void UpdatePanelSlotBlink(int slot);

BOOL UpdatePanelPromptInput(void)
{
    PanelState *panel = gPanelState;

    if (gPreviousPanelActive == 0) {
        return TRUE;
    }
    if (panel->confirmed != 0) {
        UpdateSoundAndSceneScriptSkip();
        return TRUE;
    }
    if (panel->field_b8 == 0) {
        PlaySoundEffect(0, 3);
        ResetPanelFieldB8AndNotify();
        return TRUE;
    }
    if (panel->fadePending == 0) {
        if (gPadPressedStorage & 8) {
            PlaySoundEffect(0, 3);
            ResetPanelFieldB8AndNotify();
            return TRUE;
        }
        if (panel->field_bc == 0) {
            UpdatePanelPromptBlink();
            QueuePanelScreenTransferAndUpdateSound();
            return TRUE;
        }
        if (!ToggleSelectedPanelSlot() && (gPadPressedStorage & 1)) {
            if (panel->selectedSlot == 0) {
                ResetPanelFieldB8AndNotify();
            } else {
                RequestCurrentSceneScriptSkip();
                StopSequencePlayersFrom2();
                panel->confirmed = 1;
            }
            PlaySoundEffect(0, 1);
            return TRUE;
        }
    }
    UpdatePanelPromptBlink();
    UpdatePanelSlotBlink(panel->selectedSlot);
    QueuePanelScreenTransferAndUpdateSound();
    return TRUE;
}
