#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv081Screen(void);
extern void ScrollListBackward(void);
extern void ScrollListForward(void);
extern void func_ov081_020c5478(void);
extern void DestroyOv081Screen(void);
extern void func_ov081_020c5a78(void);

void *data_ov081_020c5cc0[17] = {
    (void *)InitOv081Screen,
    (void *)DestroyOv081Screen,
    (void *)func_ov081_020c5478,
    (void *)0x0000000B,
    (void *)0x000063E8,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)func_ov081_020c5a78,
    NULL,
    NULL,
    (void *)ScrollListBackward,
    (void *)ScrollListForward,
    NULL,
    (void *)func_ov081_020c5a78,
};
