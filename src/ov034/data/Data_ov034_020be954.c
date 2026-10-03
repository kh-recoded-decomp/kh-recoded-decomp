#include "nitro/types.h"

extern u8 data_ov034_020be948[];
extern u8 data_ov034_020be94c[];
extern u8 data_ov034_020be950[];

void (*data_ov034_020be954[3])(void) = {
    (void (*)(void))data_ov034_020be94c,
    (void (*)(void))data_ov034_020be948,
    (void (*)(void))data_ov034_020be950,
};
