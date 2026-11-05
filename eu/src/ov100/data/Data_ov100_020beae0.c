#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv100SecondaryMenu(void);
extern void DestroyOv100SecondaryMenu(void);
extern void UpdateOv100SecondaryMenu(void);

void *data_ov100_020beae0[16] = {
    (void *)InitOv100SecondaryMenu,
    (void *)DestroyOv100SecondaryMenu,
    (void *)UpdateOv100SecondaryMenu,
    (void *)0x00000004,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};
