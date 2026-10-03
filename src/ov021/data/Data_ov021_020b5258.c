#include "nitro/types.h"

extern void CreateEffectTask_020acedc(void);
extern void CreateLayerTask_020acdc0(void);
extern void DispatchCommandHandler_020ad508(void);
extern void func_ov021_020ad154(void);
extern void func_ov055_020d3ddc(void);

void (*data_ov021_020b5258[7])(void) = {
    NULL,
    CreateLayerTask_020acdc0,
    CreateEffectTask_020acedc,
    func_ov021_020ad154,
    DispatchCommandHandler_020ad508,
    func_ov055_020d3ddc,
    func_ov021_020ad154,
};
