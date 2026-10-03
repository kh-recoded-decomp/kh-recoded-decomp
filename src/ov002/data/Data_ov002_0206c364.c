#include "nitro/types.h"

extern u8 data_ov002_0206c374[];
extern u8 data_ov002_0206c388[];
extern u8 data_ov002_0206c39c[];
extern u8 data_ov002_0206c3b0[];

void (*data_ov002_0206c364[4])(void) = {
    (void (*)(void))data_ov002_0206c374,
    (void (*)(void))data_ov002_0206c39c,
    (void (*)(void))data_ov002_0206c3b0,
    (void (*)(void))data_ov002_0206c388,
};
