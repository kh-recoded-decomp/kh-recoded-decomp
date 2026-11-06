#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv096SecondaryMenu(void);
extern void DestroyOv096SecondaryMenu(void);
extern void UpdateOv096SecondaryMenu(void);

void *gOv096SecondaryMenuDescriptor[16] = {
    (void *)InitOv096SecondaryMenu,
    (void *)DestroyOv096SecondaryMenu,
    (void *)UpdateOv096SecondaryMenu,
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
