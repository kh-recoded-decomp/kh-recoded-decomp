#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CancelSaveSelectStep(void);
extern void ConfirmSaveSelectStep(void);
extern void ConfirmSelectedSlot(void);
extern void DestroySaveSelectScreen(void);
extern void InitSaveSelectScreen(void);
extern void SelectSlotOnDown(void);
extern void SelectSlotOnUp(void);
extern void ToggleOptionOnLeft(void);
extern void ToggleOptionOnRight(void);
extern void UpdateSaveSelectScreen(void);
extern void SaveSelect_ConsumeLButtonNoop(void);
extern void SaveSelect_ConsumeRButtonNoop(void);

void *data_ov080_020c5da0[17] = {
    (void *)InitSaveSelectScreen,
    (void *)DestroySaveSelectScreen,
    (void *)UpdateSaveSelectScreen,
    NULL,
    (void *)0x0000A928,
    (void *)SelectSlotOnUp,
    (void *)SelectSlotOnDown,
    (void *)ToggleOptionOnLeft,
    (void *)ToggleOptionOnRight,
    (void *)ConfirmSaveSelectStep,
    (void *)CancelSaveSelectStep,
    NULL,
    (void *)ConfirmSelectedSlot,
    (void *)SaveSelect_ConsumeLButtonNoop,
    (void *)SaveSelect_ConsumeRButtonNoop,
    NULL,
    NULL,
};
