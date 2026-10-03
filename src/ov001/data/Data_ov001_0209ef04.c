#include "nitro/types.h"

extern void CheckTimerExpired_0207a0e8(void);
extern void UpdateMessageWindow_02079ff8(void);
extern void UpdateModeWidget_0207a11c(void);
extern void _fp_init_0207a118(void);
extern void func_ov001_02079f80(void);

void (*data_ov001_0209ef04[8])(void) = {
    NULL,
    NULL,
    NULL,
    func_ov001_02079f80,
    UpdateMessageWindow_02079ff8,
    CheckTimerExpired_0207a0e8,
    _fp_init_0207a118,
    UpdateModeWidget_0207a11c,
};
