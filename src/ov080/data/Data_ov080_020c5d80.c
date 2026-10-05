#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CancelSaveSelectStep_020c5c08(void);
extern void ConfirmSaveSelectStep_020c5a0c(void);
extern void ConfirmSelectedSlot_020c5cb4(void);
extern void DestroySaveSelectScreen_020c4ad0(void);
extern void SelectSlotOnDown_020c5968(void);
extern void SelectSlotOnUp_020c5924(void);
extern void ToggleOptionOnLeft_020c59ac(void);
extern void ToggleOptionOnRight_020c59dc(void);
extern void UpdateSaveSelectScreen_020c4740(void);
extern void _fp_init_020c5d08(void);
extern void _fp_init_020c5d0c(void);
extern void func_ov080_020c42b0(void);

void *data_ov080_020c5d80[17] = {
    (void *)func_ov080_020c42b0,
    (void *)DestroySaveSelectScreen_020c4ad0,
    (void *)UpdateSaveSelectScreen_020c4740,
    NULL,
    (void *)0x0000A928,
    (void *)SelectSlotOnUp_020c5924,
    (void *)SelectSlotOnDown_020c5968,
    (void *)ToggleOptionOnLeft_020c59ac,
    (void *)ToggleOptionOnRight_020c59dc,
    (void *)ConfirmSaveSelectStep_020c5a0c,
    (void *)CancelSaveSelectStep_020c5c08,
    NULL,
    (void *)ConfirmSelectedSlot_020c5cb4,
    (void *)_fp_init_020c5d08,
    (void *)_fp_init_020c5d0c,
    NULL,
    NULL,
};
