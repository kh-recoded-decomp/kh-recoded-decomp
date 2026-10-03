#include "nitro/types.h"

extern u8 data_ov091_020c2a5c[];
extern u8 data_ov091_020c2a70[];
extern u8 data_ov091_020c2a84[];
extern u8 data_ov091_020c2a9c[];

void (*data_ov091_020c2a24[3])(void) = {
    (void (*)(void))data_ov091_020c2a5c,
    (void (*)(void))data_ov091_020c2a70,
    (void (*)(void))data_ov091_020c2a84,
};

void (*data_ov091_020c2a20[1])(void) = {
    (void (*)(void))data_ov091_020c2a9c,
};
