#include "nitro/types.h"

extern void RunFadeInStep(void);
extern void func_ov103_020c0338(void);
extern void InitTheaterReportScreen(void);
extern void func_ov103_020c0490(void);

void *const data_ov103_020c049c[4] = {
    (void *)func_ov103_020c0338,
    (void *)InitTheaterReportScreen,
    (void *)RunFadeInStep,
    (void *)func_ov103_020c0490,
};
