#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv090SecondaryMenu(void);
extern void DestroyOv090SecondaryMenu(void);
extern void UpdateOv090SecondaryMenu(void);

void *data_ov090_020beae0[16] = {
    (void *)InitOv090SecondaryMenu,
    (void *)DestroyOv090SecondaryMenu,
    (void *)UpdateOv090SecondaryMenu,
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
