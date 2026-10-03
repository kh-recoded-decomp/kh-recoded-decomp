#include "nitro/types.h"

extern void *data_ov043_020bd2c0;
extern void func_ov043_020bcbcc(int arg, void *camera);

void ResetCameraDefault_020bcbb0(void) {
    func_ov043_020bcbcc(0, data_ov043_020bd2c0);
}
