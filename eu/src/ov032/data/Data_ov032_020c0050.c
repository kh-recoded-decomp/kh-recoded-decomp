#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitGroupMenuGauge(void);
extern void ReleaseGroupResourceBuffers(void);

void *gGroupMenuGaugeTaskClass[5] = {
    (void *)0x000E0015,
    (void *)InitGroupMenuGauge,
    (void *)ReleaseGroupResourceBuffers,
    (void *)0x0000002C,
    NULL,
};
