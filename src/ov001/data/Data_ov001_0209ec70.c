#include "nitro/types.h"

extern u8 data_ov001_0209ec40[];
extern void CheckSceneTimeout_02070338(void);
extern void UpdateHudSlideTween_020702c0(void);
extern void func_ov001_0207031c(void);

void (*data_ov001_0209ec78[5])(void) = {
    NULL,
    UpdateHudSlideTween_020702c0,
    func_ov001_0207031c,
    CheckSceneTimeout_02070338,
    UpdateHudSlideTween_020702c0,
};

void (*data_ov001_0209ec70[2])(void) = {
    (void (*)(void))data_ov001_0209ec40,
    (void (*)(void))data_ov001_0209ec40,
};
