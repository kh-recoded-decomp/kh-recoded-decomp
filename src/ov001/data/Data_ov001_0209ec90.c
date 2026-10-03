#include "nitro/types.h"

extern u8 data_ov001_0209ec48[];
extern u8 data_ov001_0209ec50[];
extern u8 data_ov001_0209ec8c[];

void (*data_ov001_0209ec90[3])(void) = {
    (void (*)(void))data_ov001_0209ec48,
    (void (*)(void))data_ov001_0209ec8c,
    (void (*)(void))data_ov001_0209ec50,
};
