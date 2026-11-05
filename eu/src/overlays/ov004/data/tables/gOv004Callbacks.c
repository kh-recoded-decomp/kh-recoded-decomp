#include "nitro/types.h"

extern void SetScrollMainBlendBrightness(void);
extern void ClearScrollMainBlendControl(void);
extern void SetScrollSubBlendBrightness(void);
extern void ClearScrollSubBlendControl(void);

void (*const gOv004Callbacks[4])(void) = {
    SetScrollMainBlendBrightness,
    ClearScrollMainBlendControl,
    SetScrollSubBlendBrightness,
    ClearScrollSubBlendControl,
};
