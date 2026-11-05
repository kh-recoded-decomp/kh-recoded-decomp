#include "nitro/types.h"

extern void InitSpinCameraOrbit(void); /* InitSpinCameraOrbit */
extern void InitFastSpinCameraOrbit(void); /* InitFastSpinCameraOrbit */
extern void InitEventCameraMotionPreset2(void);
extern void InitEventCameraMotionPreset3(void);
extern void InitRandomCameraSwing(void); /* InitRandomCameraSwing */
extern void InitRandomCameraSway(void); /* InitRandomCameraSway */

void (*gCameraMotionInitializers[6])(void) = {
    InitSpinCameraOrbit, /* InitSpinCameraOrbit */
    InitFastSpinCameraOrbit, /* InitFastSpinCameraOrbit */
    InitEventCameraMotionPreset2,
    InitEventCameraMotionPreset3,
    InitRandomCameraSwing, /* InitRandomCameraSwing */
    InitRandomCameraSway, /* InitRandomCameraSway */
};
