#include "nitro/types.h"

typedef struct TwoDigitValues {
    u8 first;
    u8 second;
} TwoDigitValues;

extern TwoDigitValues *data_ov001_020a04d0;
extern void ShowTwoDigitCounters_0207d984(TwoDigitValues *values);

void IncrementAndShowCounter_0207e0f0(void)
{
    TwoDigitValues *values = data_ov001_020a04d0;

    values->first++;
    ShowTwoDigitCounters_0207d984(values);
}
