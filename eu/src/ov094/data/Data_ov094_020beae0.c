#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv094SecondaryMenu(void);
extern void DestroyOv094SecondaryMenu(void);
extern void UpdateOv094SecondaryMenu(void);

void *gOv094SecondaryMenuDescriptor[16] = {
    (void *)InitOv094SecondaryMenu,
    (void *)DestroyOv094SecondaryMenu,
    (void *)UpdateOv094SecondaryMenu,
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
