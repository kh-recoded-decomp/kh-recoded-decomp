#include "nitro/types.h"

extern u8 data_ov052_020d2140[];
extern u8 data_ov052_020d2148[];
extern u8 data_ov052_020d2150[];
extern u8 data_ov052_020d215c[];

void (*data_ov052_020d216c[4])(void) = {
    (void (*)(void))data_ov052_020d2150,
    (void (*)(void))data_ov052_020d215c,
    (void (*)(void))data_ov052_020d2140,
    (void (*)(void))data_ov052_020d2148,
};
