#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov043_020bd2c0;
extern VecFx32 *GetSubStruct1C_020bbfe0(void);
extern void RotateVectorAroundAxis_0204b34c(VecFx32 *vec, const VecFx32 *axis, s32 angle);

void RotateCameraUp_020bca9c(s32 angle) {
    u8 *camera;
    if (angle == 0) {
        return;
    }
    camera = data_ov043_020bd2c0;
    RotateVectorAroundAxis_0204b34c((VecFx32 *)(camera + 0x2c), GetSubStruct1C_020bbfe0(), angle);
}
