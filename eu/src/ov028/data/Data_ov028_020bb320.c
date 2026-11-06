#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitFieldOverlayState(void);
extern void ReleaseFieldContext(void);

void *gOv028FieldSceneTaskClass[5] = {
    (void *)0x0002000E,
    (void *)InitFieldOverlayState,
    (void *)ReleaseFieldContext,
    (void *)0x00000024,
    NULL,
};

u32 gOv028FieldSceneTaskHandle[1] = {
    0xFFFFFFFF,
};
