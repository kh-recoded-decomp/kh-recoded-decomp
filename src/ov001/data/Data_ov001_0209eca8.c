#include "nitro/types.h"

extern u8 data_ov001_0209ec5c[];
extern u8 data_ov001_0209ec60[];
extern u8 data_ov001_0209ec6c[];

void (*data_ov001_0209eca8[3])(void) = {
    (void (*)(void))data_ov001_0209ec60,
    (void (*)(void))data_ov001_0209ec5c,
    (void (*)(void))data_ov001_0209ec6c,
};
