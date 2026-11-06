#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv098SecondaryMenu(void);
extern void DestroyOv098SecondaryMenu(void);
extern void UpdateOv098SecondaryMenu(void);

void *gOv098SecondaryMenuDescriptor[16] = {
    (void *)InitOv098SecondaryMenu,
    (void *)DestroyOv098SecondaryMenu,
    (void *)UpdateOv098SecondaryMenu,
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
