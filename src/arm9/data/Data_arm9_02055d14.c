#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitMatColorAnmMap_0201c43c(void);
extern void InitTexSRTAnmMap_0201c910(void);
extern void InitializeJointAnimationMap_0201ae04(void);
extern void InitializeTexturePatternMap_0201ca3c(void);
extern void InitializeVisibilityAnimationMap_0201ccd8(void);

void *data_02055d18[19] = {
    (void *)InitMatColorAnmMap_0201c43c,
    (void *)0x5450004D,
    (void *)InitializeTexturePatternMap_0201ca3c,
    (void *)0x5441004D,
    (void *)InitTexSRTAnmMap_0201c910,
    (void *)0x56410056,
    (void *)InitializeVisibilityAnimationMap_0201ccd8,
    (void *)0x4341004A,
    (void *)InitializeJointAnimationMap_0201ae04,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

u32 data_02055d14[1] = {
    0x4D41004D,
};
