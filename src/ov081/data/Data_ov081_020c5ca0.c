#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroyOv081Screen_020c571c(void);
extern void InitOv081Screen_020c4c30(void);
extern void PXI_Init_020c5458(void);
extern void ScrollListBackward_020c5b2c(void);
extern void ScrollListForward_020c5b84(void);
extern void func_ov081_020c5a58(void);

void *data_ov081_020c5ca0[17] = {
    (void *)InitOv081Screen_020c4c30,
    (void *)DestroyOv081Screen_020c571c,
    (void *)PXI_Init_020c5458,
    (void *)0x0000000B,
    (void *)0x000063E8,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)func_ov081_020c5a58,
    NULL,
    NULL,
    (void *)ScrollListBackward_020c5b2c,
    (void *)ScrollListForward_020c5b84,
    NULL,
    (void *)func_ov081_020c5a58,
};
