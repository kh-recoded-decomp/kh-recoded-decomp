#include "src/graphics/CameraState.h"

#pragma explicit_zero_data on

extern void MSL_FpInitB(void);

void *gManagerObjectDescriptorB[5] = {
    (void *)0x0011001D,
    (void *)GetSavedCameraRestoreCallback,
    (void *)MSL_FpInitB,
    NULL,
    NULL,
};
