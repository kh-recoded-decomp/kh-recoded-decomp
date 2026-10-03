#include "nitro/types.h"

extern void DisableOv029Sound_020ba768(void);
extern void EnableOv029Sound_020ba670(void);
extern void HandleOverlayExitFlag_020ba708(void);
extern void MarkSoundCtxActive_020ba5a0(void);
extern void func_ov029_020ba568(void);
extern void func_ov029_020ba5c8(void);
extern void func_ov029_020ba5dc(void);
extern void func_ov029_020ba824(void);

void (*data_ov029_020bab78[8])(void) = {
    func_ov029_020ba568,
    MarkSoundCtxActive_020ba5a0,
    func_ov029_020ba5c8,
    func_ov029_020ba5dc,
    EnableOv029Sound_020ba670,
    HandleOverlayExitFlag_020ba708,
    DisableOv029Sound_020ba768,
    func_ov029_020ba824,
};
