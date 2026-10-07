#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyRecordMenu(void);
extern void InitRecordMenu(void);
extern void ReturnToPrimaryPanel(void);
extern void StepCursorBackward(void);
extern void StepCursorForward_020c0e10(void);
extern void UpdateRecordPanelInput(void);

u32 data_ov086_020c2368[6] = {
    0x00000004, 0x00000001, 0x00000005, 0x00000002,
    0x00000004, 0x00000000,
};
