#include "nitro/types.h"

extern u8 data_ov103_020c050c[];
extern u8 data_ov103_020c0524[];
extern u8 data_ov103_020c053c[];
extern u8 data_ov103_020c055c[];
extern u8 data_ov103_020c0580[];

void (*data_ov103_020c04a8[3])(void) = {
    (void (*)(void))data_ov103_020c053c,
    (void (*)(void))data_ov103_020c0580,
    (void (*)(void))data_ov103_020c055c,
};

void (*data_ov103_020c04a0[2])(void) = {
    (void (*)(void))data_ov103_020c050c,
    (void (*)(void))data_ov103_020c0524,
};
