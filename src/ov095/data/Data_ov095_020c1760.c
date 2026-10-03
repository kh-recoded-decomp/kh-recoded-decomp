#include "nitro/types.h"

extern u8 data_ov095_020c17d0[];
extern u8 data_ov095_020c17e4[];
extern u8 data_ov095_020c17fc[];
extern u8 data_ov095_020c1818[];
extern u8 data_ov095_020c1834[];

void (*data_ov095_020c1768[3])(void) = {
    (void (*)(void))data_ov095_020c17d0,
    (void (*)(void))data_ov095_020c17e4,
    (void (*)(void))data_ov095_020c17fc,
};

void (*data_ov095_020c1760[2])(void) = {
    (void (*)(void))data_ov095_020c1834,
    (void (*)(void))data_ov095_020c1818,
};
