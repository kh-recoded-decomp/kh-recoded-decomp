#include "nitro/types.h"

extern u8 data_ov002_0206c290[];
extern u8 data_ov002_0206c2a0[];
extern u8 data_ov002_0206c2b0[];
extern u8 data_ov002_0206c2d8[];

void (*data_ov002_0206c280[4])(void) = {
    (void (*)(void))data_ov002_0206c2d8,
    (void (*)(void))data_ov002_0206c2b0,
    (void (*)(void))data_ov002_0206c2a0,
    (void (*)(void))data_ov002_0206c290,
};
