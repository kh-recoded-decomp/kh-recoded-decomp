#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv102SecondaryMenu(void);
extern void DestroyOv102SecondaryMenu(void);
extern void UpdateOv102SecondaryMenu(void);

void *gOv102SecondaryMenuDescriptor[16] = {
    (void *)InitOv102SecondaryMenu,
    (void *)DestroyOv102SecondaryMenu,
    (void *)UpdateOv102SecondaryMenu,
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
