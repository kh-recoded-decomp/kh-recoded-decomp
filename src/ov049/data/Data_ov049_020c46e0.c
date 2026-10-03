#include "nitro/types.h"

extern void InitFastSpinCameraOrbit_020c353c(void);
extern void InitRandomCameraSway_020c35e4(void);
extern void InitRandomCameraSwing_020c35b4(void);
extern void InitSpinCameraOrbit_020c3500(void);
extern void func_ov049_020c357c(void);
extern void func_ov049_020c3598(void);

void (*data_ov049_020c46e0[6])(void) = {
    InitSpinCameraOrbit_020c3500,
    InitFastSpinCameraOrbit_020c353c,
    func_ov049_020c357c,
    func_ov049_020c3598,
    InitRandomCameraSwing_020c35b4,
    InitRandomCameraSway_020c35e4,
};
