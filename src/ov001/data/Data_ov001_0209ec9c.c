#include "nitro/types.h"

extern u8 data_ov001_0209ec58[];
extern u8 data_ov001_0209ec64[];
extern u8 data_ov001_0209ec68[];

void (*data_ov001_0209ec9c[3])(void) = {
    (void (*)(void))data_ov001_0209ec64,
    (void (*)(void))data_ov001_0209ec58,
    (void (*)(void))data_ov001_0209ec68,
};
