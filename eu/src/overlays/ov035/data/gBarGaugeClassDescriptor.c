#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitBarGauge(void);
extern void ReleaseAreaGaugeBuffers(void);

void *gBarGaugeClassDescriptor[6] = {
    (void *)0x000E000C,
    (void *)InitBarGauge,
    (void *)ReleaseAreaGaugeBuffers,
    (void *)0x00000138,
    NULL,
    NULL,
};
