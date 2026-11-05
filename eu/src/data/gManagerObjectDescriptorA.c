#include "src/graphics/CameraState.h"

#pragma explicit_zero_data on

extern void MSL_FpInitA(void);

void *gManagerObjectDescriptorA[5] = {
    (void *)0x00110011,
    (void *)GetOrthographicCameraBeginCallback,
    (void *)MSL_FpInitA,
    NULL,
    NULL,
};
