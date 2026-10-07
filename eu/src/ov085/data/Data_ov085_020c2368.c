#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DecreasePickerValue(void);
extern void IncreasePickerValue(void);
extern void StepPickerBack(void);
extern void func_ov085_020c0154(void);

void *data_ov085_020c2368[6] = {
    (void *)func_ov085_020c0154,
    (void *)0x00000001,
    (void *)0x00005EA8,
    (void *)IncreasePickerValue,
    (void *)DecreasePickerValue,
    (void *)StepPickerBack,
};
