#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitScoreScreen(void);
extern void ReleaseScreenResources_020bf310(void);
extern void UpdateScoreScreen(void);

void *data_ov083_020bf6a0[16] = {
    (void *)InitScoreScreen,
    (void *)ReleaseScreenResources_020bf310,
    (void *)UpdateScoreScreen,
    (void *)0x0000076C,
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
    NULL,
    NULL,
};
