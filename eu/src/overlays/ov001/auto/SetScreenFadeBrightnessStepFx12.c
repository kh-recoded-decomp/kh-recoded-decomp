#include "nitro/types.h"

extern u8 *gFieldScreenTransitionWork;

void SetScreenFadeBrightnessStepFx12(u32 value)
{
    *(u32 *)(gFieldScreenTransitionWork + 0x1c) = value;
}
