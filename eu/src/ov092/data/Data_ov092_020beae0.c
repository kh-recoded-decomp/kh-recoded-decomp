#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv092SecondaryMenu(void);
extern void DestroyOv092SecondaryMenu(void);
extern void UpdateOv092SecondaryMenu(void);

void *data_ov092_020beae0[16] = {
    (void *)InitOv092SecondaryMenu,
    (void *)DestroyOv092SecondaryMenu,
    (void *)UpdateOv092SecondaryMenu,
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
