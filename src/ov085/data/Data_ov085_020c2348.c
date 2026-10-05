#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DecreasePickerValue_020c15bc(void);
extern void IncreasePickerValue_020c1588(void);
extern void StepPickerBack_020c15f0(void);
extern void UpdateItemListScroll_020c0134(void);

void *data_ov085_020c2348[6] = {
    (void *)UpdateItemListScroll_020c0134,
    (void *)0x00000001,
    (void *)0x00005EA8,
    (void *)IncreasePickerValue_020c1588,
    (void *)DecreasePickerValue_020c15bc,
    (void *)StepPickerBack_020c15f0,
};
