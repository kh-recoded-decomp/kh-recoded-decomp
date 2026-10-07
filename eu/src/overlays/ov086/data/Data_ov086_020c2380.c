#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyRecordMenu(void);
extern void InitRecordMenu(void);
extern void ReturnToPrimaryPanel(void);
extern void StepCursorBackward(void);
extern void StepCursorForward_020c0e10(void);
extern void UpdateRecordPanelInput(void);

void *gRecordMenuCommandTable[16] = {
    (void *)InitRecordMenu,
    (void *)DestroyRecordMenu,
    (void *)UpdateRecordPanelInput,
    (void *)0x000001EC,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)ReturnToPrimaryPanel,
    (void *)ReturnToPrimaryPanel,
    NULL,
    (void *)StepCursorBackward,
    (void *)StepCursorForward_020c0e10,
    NULL,
    NULL,
};
