#include "nitro/types.h"

extern u8 data_ov001_0209ec44[];
extern u8 data_ov001_0209ec4c[];
extern u8 data_ov001_0209ec54[];

void (*data_ov001_0209ecb4[3])(void) = {
    (void (*)(void))data_ov001_0209ec4c,
    (void (*)(void))data_ov001_0209ec54,
    (void (*)(void))data_ov001_0209ec44,
};
